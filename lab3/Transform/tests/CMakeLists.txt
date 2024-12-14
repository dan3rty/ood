add_executable(TransformTest
               Transform.test.cpp
               ../OutputDataStream/IOutputDataStream.h
               ../OutputDataStream/FileOutputStream/CFileOutputStream.cpp
               ../OutputDataStream/FileOutputStream/CFileOutputStream.h
               ../OutputDataStream/MemoryOutputStream/CMemoryOutputStream.cpp
               ../OutputDataStream/MemoryOutputStream/CMemoryOutputStream.h
               ../InputDataStream/IInputDataStream.h
               ../InputDataStream/FileInputStream/CFileInputStream.cpp
               ../InputDataStream/FileInputStream/CFileInputStream.h
               ../InputDataStream/MemoryInputStream/CMemoryInputStream.cpp
               ../InputDataStream/MemoryInputStream/CMemoryInputStream.h
               ../InputDataStreamDecorator/CInputDataStreamDecorator.cpp
               ../InputDataStreamDecorator/CInputDataStreamDecorator.h
               ../InputDataStreamDecorator/DecryptingInputStream/CDecryptingInputStream.cpp
               ../InputDataStreamDecorator/DecryptingInputStream/CDecryptingInputStream.h
               ../InputDataStreamDecorator/DecompressingInputStream/CDecompressingInputStream.cpp
               ../InputDataStreamDecorator/DecompressingInputStream/CDecompressingInputStream.h
               ../OutputDataStreamDecorator/EncryptingOutputStream/CEncryptingOutputStream.cpp
               ../OutputDataStreamDecorator/EncryptingOutputStream/CEncryptingOutputStream.h
               ../OutputDataStreamDecorator/CompressingOutputStream/CCompressingOutputStream.cpp
               ../OutputDataStreamDecorator/CompressingOutputStream/CCompressingOutputStream.h
               ../EncryptionTableBuilder/CEncryptionTableBuilder.cpp
               ../EncryptionTableBuilder/CEncryptionTableBuilder.h)

target_link_libraries(TransformTest PUBLIC catch2)
add_test(NAME TransformTest COMMAND TransformTest)
