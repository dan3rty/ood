#define CATCH_CONFIG_MAIN
#include "../InputDataStream/FileInputStream/CFileInputStream.h"
#include "../InputDataStream/MemoryInputStream/CMemoryInputStream.h"
#include "../InputDataStreamDecorator/DecompressingInputStream/CDecompressingInputStream.h"
#include "../InputDataStreamDecorator/DecryptingInputStream/CDecryptingInputStream.h"
#include "../OutputDataStream/FileOutputStream/CFileOutputStream.h"
#include "../OutputDataStream/MemoryOutputStream/CMemoryOutputStream.h"
#include "../OutputDataStreamDecorator/EncryptingOutputStream/CEncryptingOutputStream.h"
#include "catch.hpp"
#include <filesystem>

std::vector<std::uint8_t> GetFileContents(std::string const& filename)
{
	std::ifstream stream(filename, std::ios_base::in | std::ios_base::binary);
	stream.unsetf(std::ios::skipws);

	const std::istream_iterator<std::uint8_t> begin(stream), end;
	std::vector result(begin, end);

	return result;
}

std::string GetTemporaryFilepath()
{
	auto const tempDir = std::filesystem::temp_directory_path();
	auto const result = tempDir / "output.txt";

	return result.string();
}

SCENARIO("File input stream")
{
	GIVEN("non existing file path")
	{
		std::string const path = "non-existing-file.txt";

		WHEN("creating a stream")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(CFileInputStream(path), std::runtime_error);
			}
		}
	}

	GIVEN("a stream with empty data")
	{
		auto const data = GetFileContents("empty.txt");
		CFileInputStream stream("empty.txt");

		THEN("it is at EOF")
		{
			REQUIRE(stream.IsEOF());
		}

		WHEN("reading a byte")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
			}
		}

		WHEN("reading a block")
		{
			constexpr std::size_t size = 10;
			std::vector<std::uint8_t> bytes(size);
			bytes[0] = '!';
			bytes[1] = '!';
			bytes[2] = '!';
			stream.ReadBlock(bytes.data(), size);

			THEN("destination buffer is not changed")
			{
				REQUIRE(bytes[0] == '!');
				REQUIRE(bytes[1] == '!');
				REQUIRE(bytes[2] == '!');
			}
		}
	}

	GIVEN("a stream with sample data")
	{
		auto const data = GetFileContents("test.txt");
		CFileInputStream stream("test.txt");

		THEN("it is not at EOF")
		{
			REQUIRE_FALSE(stream.IsEOF());
		}

		WHEN("reading by bytes")
		{
			THEN("data matches initial")
			{
				for (auto&& ch : data)
				{
					REQUIRE(stream.ReadByte() == ch);
				}

				AND_WHEN("all data has been read")
				{
					THEN("it is at EOF")
					{
						REQUIRE(stream.IsEOF());
					}

					THEN("attempting to read byte throws an exception")
					{
						REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
					}
				}
			}
		}

		WHEN("reading some characters by block")
		{
			constexpr std::size_t size = 2;
			std::vector<std::uint8_t> bytes(size);
			stream.ReadBlock(bytes.data(), size);

			THEN("data matches initial")
			{
				REQUIRE(std::memcmp(data.data(), bytes.data(), size) == 0);
			}

			THEN("it is not at EOF")
			{
				REQUIRE_FALSE(stream.IsEOF());
			}

			THEN("next byte is read correctly")
			{
				REQUIRE(stream.ReadByte() == data[size]);
			}
		}

		WHEN("reading everything by block")
		{
			std::vector<std::uint8_t> bytes(data.size());
			stream.ReadBlock(bytes.data(), static_cast<std::streamsize>(data.size()));

			THEN("data matches initial")
			{
				REQUIRE(data == bytes);
			}

			THEN("attempting to read byte throws an exception")
			{
				REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
			}
		}

		WHEN("reading more characters than there is in the stream")
		{
			std::vector<std::uint8_t> bytes(data.size());
			stream.ReadBlock(bytes.data(), static_cast<std::streamsize>(data.size() + 10));

			THEN("data matches initial")
			{
				REQUIRE(data == bytes);
			}

			THEN("attempting to read byte throws an exception")
			{
				REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
			}
		}
	}
}

SCENARIO("File output stream")
{
	GIVEN("unavailable file path")
	{
		std::string const path = "/unavailable/path/file.txt";

		WHEN("creating a stream")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(CFileOutputStream(path), std::runtime_error);
			}
		}
	}

	GIVEN("a stream")
	{
		auto const filepath = GetTemporaryFilepath();
		CFileOutputStream stream(filepath);

		WHEN("writing a couple of bytes")
		{
			stream.WriteByte('a');
			stream.WriteByte('b');
			stream.WriteByte('c');

			THEN("data vector becomes populated with these bytes")
			{
				REQUIRE(GetFileContents(filepath) == std::vector<std::uint8_t>{ 'a', 'b', 'c' });
			}

			AND_WHEN("writing a subsequent block of bytes")
			{
				std::vector<std::uint8_t> bytes = { 'd', 'e', 'f', 'g' };
				stream.WriteBlock(bytes.data(), static_cast<std::streamsize>(bytes.size()));

				THEN("data vector becomes populated with new bytes")
				{
					REQUIRE(GetFileContents(filepath) == std::vector<std::uint8_t>{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' });
				}
			}
		}

		WHEN("writing a block of bytes")
		{
			std::vector<std::uint8_t> bytes = { 'd', 'e', 'f', 'g' };
			stream.WriteBlock(bytes.data(), static_cast<std::streamsize>(bytes.size()));

			THEN("data vector matches written bytes")
			{
				REQUIRE(GetFileContents(filepath) == bytes);
			}

			AND_WHEN("writing some bytes")
			{
				stream.WriteByte('a');
				stream.WriteByte('b');

				THEN("data vector becomes populated with new bytes")
				{
					REQUIRE(GetFileContents(filepath) == std::vector<std::uint8_t>{ 'd', 'e', 'f', 'g', 'a', 'b' });
				}
			}
		}
	}
}

SCENARIO("Memory input stream")
{
	GIVEN("a stream with empty data")
	{
		std::vector<std::uint8_t> data;
		CMemoryInputStream stream(data);

		THEN("it is at EOF")
		{
			REQUIRE(stream.IsEOF());
		}

		WHEN("reading a byte")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
			}
		}

		WHEN("reading a block")
		{
			constexpr std::size_t size = 10;
			std::vector<std::uint8_t> bytes(size);
			bytes[0] = '!';
			bytes[1] = '!';
			bytes[2] = '!';
			stream.ReadBlock(bytes.data(), size);

			THEN("destination buffer is not changed")
			{
				REQUIRE(bytes[0] == '!');
				REQUIRE(bytes[1] == '!');
				REQUIRE(bytes[2] == '!');
			}
		}
	}

	GIVEN("a stream with sample data")
	{
		std::vector<std::uint8_t> data = { 'H', 'e', 'l', 'l', 'o' };
		CMemoryInputStream stream(data);

		THEN("it is not at EOF")
		{
			REQUIRE_FALSE(stream.IsEOF());
		}

		WHEN("reading by bytes")
		{
			THEN("data matches initial")
			{
				for (auto&& ch : data)
				{
					REQUIRE(stream.ReadByte() == ch);
				}

				AND_WHEN("all data has been read")
				{
					THEN("it is at EOF")
					{
						REQUIRE(stream.IsEOF());
					}

					THEN("attempting to read byte throws an exception")
					{
						REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
					}
				}
			}
		}

		WHEN("reading some characters by block")
		{
			constexpr std::size_t size = 2;
			std::vector<std::uint8_t> bytes(size);
			stream.ReadBlock(bytes.data(), size);

			THEN("data matches initial")
			{
				REQUIRE(std::memcmp(data.data(), bytes.data(), size) == 0);
			}

			THEN("it is not at EOF")
			{
				REQUIRE_FALSE(stream.IsEOF());
			}

			THEN("next byte is read correctly")
			{
				REQUIRE(stream.ReadByte() == data[size]);
			}
		}

		WHEN("reading everything by block")
		{
			std::vector<std::uint8_t> bytes(data.size());
			stream.ReadBlock(bytes.data(), static_cast<std::streamsize>(data.size()));

			THEN("data matches initial")
			{
				REQUIRE(data == bytes);
			}

			THEN("attempting to read byte throws an exception")
			{
				REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
			}
		}

		WHEN("reading more characters than there is in the stream")
		{
			std::vector<std::uint8_t> bytes(data.size());
			stream.ReadBlock(bytes.data(), static_cast<std::streamsize>(data.size() + 10));

			THEN("data matches initial")
			{
				REQUIRE(data == bytes);
			}

			THEN("attempting to read byte throws an exception")
			{
				REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
			}
		}
	}
}

SCENARIO("Memory output stream")
{
	GIVEN("a stream")
	{
		std::vector<std::uint8_t> data;
		CMemoryOutputStream stream(data);

		WHEN("writing a couple of bytes")
		{
			stream.WriteByte('a');
			stream.WriteByte('b');
			stream.WriteByte('c');

			THEN("data vector becomes populated with these bytes")
			{
				REQUIRE(data == std::vector<std::uint8_t>{ 'a', 'b', 'c' });
			}

			AND_WHEN("writing a subsequent block of bytes")
			{
				std::vector<std::uint8_t> bytes = { 'd', 'e', 'f', 'g' };
				stream.WriteBlock(bytes.data(), static_cast<std::streamsize>(bytes.size()));

				THEN("data vector becomes populated with new bytes")
				{
					REQUIRE(data == std::vector<std::uint8_t>{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' });
				}
			}
		}

		WHEN("writing a block of bytes")
		{
			std::vector<std::uint8_t> bytes = { 'd', 'e', 'f', 'g' };
			stream.WriteBlock(bytes.data(), static_cast<std::streamsize>(bytes.size()));

			THEN("data vector matches written bytes")
			{
				REQUIRE(data == bytes);
			}

			AND_WHEN("writing some bytes")
			{
				stream.WriteByte('a');
				stream.WriteByte('b');

				THEN("data vector becomes populated with new bytes")
				{
					REQUIRE(data == std::vector<std::uint8_t>{ 'd', 'e', 'f', 'g', 'a', 'b' });
				}
			}
		}
	}
}

SCENARIO("Encrypting and decrypting streams")
{
	GIVEN("a vector for reading and writing")
	{
		std::vector<std::uint8_t> data;

		AND_GIVEN("encrypting output stream")
		{
			int key = 42;
			auto cleanOutputStream = std::make_unique<CMemoryOutputStream>(data);
			auto encryptingStream = std::make_unique<CEncryptingOutputStream>(std::move(cleanOutputStream), key);

			WHEN("encrypting a couple of bytes")
			{
				std::vector<std::uint8_t> bytes = { 'k', 'i', 'l', 'l', 'm', 'e' };
				for (auto&& byte : bytes)
				{
					encryptingStream->WriteByte(byte);
				}

				AND_WHEN("reading these bytes with input stream")
				{
					auto cleanInputStream = std::make_unique<CMemoryInputStream>(data);

					THEN("they are not equal")
					{
						for (auto&& byte : bytes)
						{
							REQUIRE(byte != cleanInputStream->ReadByte());
						}
					}
				}

				AND_WHEN("decrypting these bytes with decrypting stream and another key")
				{
					auto cleanInputStream = std::make_unique<CMemoryInputStream>(data);
					auto decryptingStream = std::make_unique<CDecryptingInputStream>(std::move(cleanInputStream), 12);

					THEN("they are not equal")
					{
						for (auto&& byte : bytes)
						{
							REQUIRE(byte != decryptingStream->ReadByte());
						}
					}
				}

				AND_WHEN("decrypting these bytes with decrypting stream and the same key")
				{
					auto cleanInputStream = std::make_unique<CMemoryInputStream>(data);
					auto decryptingStream = std::make_unique<CDecryptingInputStream>(std::move(cleanInputStream), key);

					THEN("they are equal")
					{
						for (auto&& byte : bytes)
						{
							REQUIRE(byte == decryptingStream->ReadByte());
						}
					}
				}
			}
		}
	}
}

SCENARIO("Compressing and decompressing streams")
{
	GIVEN("a vector for reading and writing")
	{
		std::vector<std::uint8_t> data;

		AND_GIVEN("clean output stream")
		{
			auto cleanOutputStream = std::make_unique<CMemoryOutputStream>(data);

			WHEN("compressing a couple of bytes")
			{
				std::vector<std::uint8_t> bytes = { 'k', 'i', 'l', 'l', 'm', 'e' };

				{
					auto compressingStream = std::make_unique<CCompressingOutputStream>(std::move(cleanOutputStream));
					for (auto&& byte : bytes)
					{
						compressingStream->WriteByte(byte);
					}
				}

				THEN("compression works correctly")
				{
					REQUIRE(data[0] == 1);
					REQUIRE(data[1] == 'k');
					REQUIRE(data[2] == 1);
					REQUIRE(data[3] == 'i');
					REQUIRE(data[4] == 2);
					REQUIRE(data[5] == 'l');
					REQUIRE(data[6] == 1);
					REQUIRE(data[7] == 'm');
					REQUIRE(data[8] == 1);
					REQUIRE(data[9] == 'e');
				}

				AND_WHEN("reading these bytes with input stream")
				{
					auto cleanInputStream = std::make_unique<CMemoryInputStream>(data);

					THEN("they are not equal")
					{
						for (auto&& byte : bytes)
						{
							REQUIRE(byte != cleanInputStream->ReadByte());
						}
					}
				}

				AND_WHEN("decompressing these bytes with decompressing stream")
				{
					auto cleanInputStream = std::make_unique<CMemoryInputStream>(data);
					auto decompressingStream = std::make_unique<CDecompressingInputStream>(std::move(cleanInputStream));

					THEN("they are equal")
					{
						for (auto&& byte : bytes)
						{
							REQUIRE(byte == decompressingStream->ReadByte());
						}
					}
				}
			}

			WHEN("compressing more bytes than one size byte can take")
			{
				{
					auto compressingStream = std::make_unique<CCompressingOutputStream>(std::move(cleanOutputStream));
					for (std::streamsize i = 0; i < std::numeric_limits<std::uint8_t>::max(); ++i)
					{
						compressingStream->WriteByte('a');
					}
					compressingStream->WriteByte('a');
					compressingStream->WriteByte('a');
					compressingStream->WriteByte('a');
				}

				THEN("overflowing compression works correctly")
				{
					REQUIRE(data[0] == std::numeric_limits<std::uint8_t>::max());
					REQUIRE(data[1] == 'a');
					REQUIRE(data[2] == 3);
					REQUIRE(data[3] == 'a');
				}
			}
		}
	}
}
