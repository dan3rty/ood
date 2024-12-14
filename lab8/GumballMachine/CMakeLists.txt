add_executable(GumballMachine
               main.cpp
               State/IState.h
               State/SoldState/CSoldState.cpp
               State/SoldState/CSoldState.h
               State/SoldOutState/CSoldOutState.cpp
               State/SoldOutState/CSoldOutState.h
               State/HasQuarterState/CHasQuarterState.cpp
               State/HasQuarterState/CHasQuarterState.h
               State/NoQuarterState/CNoQuarterState.cpp
               State/NoQuarterState/CNoQuarterState.h
               State/IGumballMachine.h
               GumballMachine/CGumballMachine.cpp
               GumballMachine/CGumballMachine.h
               Menu/CMenu.cpp
               Menu/CMenu.h)

add_subdirectory(tests)
