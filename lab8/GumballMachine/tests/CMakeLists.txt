add_executable(GumballMachineTest
               GumballMachine.test.cpp
               ../State/IState.h
               ../State/SoldState/CSoldState.cpp
               ../State/SoldState/CSoldState.h
               ../State/SoldOutState/CSoldOutState.cpp
               ../State/SoldOutState/CSoldOutState.h
               ../State/HasQuarterState/CHasQuarterState.cpp
               ../State/HasQuarterState/CHasQuarterState.h
               ../State/NoQuarterState/CNoQuarterState.cpp
               ../State/NoQuarterState/CNoQuarterState.h
               ../State/IGumballMachine.h
               ../GumballMachine/CGumballMachine.cpp
               ../GumballMachine/CGumballMachine.h)

target_link_libraries(GumballMachineTest PUBLIC catch2 fakeit)
add_test(NAME GumballMachineTest COMMAND GumballMachineTest)
