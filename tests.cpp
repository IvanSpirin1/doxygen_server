#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <vector>
#include <UnitTest++/TestReporterStdout.h>

#include <Server.h>
#include <Logger.h>
#include <UsersBase.h>

auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}

SUITE(Arguments){
    TEST(argumemnt_check_1){
        Server srv;
        
        char* cmdLine[] = {"-p","33333","-l","logs","-f","users"};
        auto result = srv.ParseCmdLine(6,cmdLine);
        CHECK(result);
    }

    TEST(argumemnt_check_2){
        Server srv;
        
        char* cmdLine[] = {"-blabla","blabla","-l","logs","-f","users"};
        auto result = srv.ParseCmdLine(6,cmdLine);
        CHECK(!result);
    }

    TEST(argumemnt_check_3){
        Server srv;
        
        char* cmdLine[] = {"-blabla","33333","-l","logs","-f","users"};
        auto result = srv.ParseCmdLine(6,cmdLine);
        CHECK(!result);
    }

    TEST(argumemnt_check_4){
        Server srv;
        
        char* cmdLine[] = {"-блабла","33333","-l","logs","-f","users"};
        auto result = srv.ParseCmdLine(6,cmdLine);
        CHECK(!result);
    }
}

SUITE(Server){

    TEST(launch_test_1){
        Server srv;
        
        char* cmdLine[] = {"-p","33333","-l","logs","-f","users"};
        srv.ParseCmdLine(6,cmdLine);
        auto result = srv.Initialize();
        CHECK(result);
    }

    TEST(launch_test_invalidPort_1){
        Server srv;
        
        char* cmdLine[] = {"-p","100000","-l","logs","-f","users"};
        srv.ParseCmdLine(6,cmdLine);
        auto result = srv.Initialize();
        CHECK(!result);
    }

    TEST(launch_test_invalidPort_2){
        Server srv;
        
        char* cmdLine[] = {"-p","3333","-l","logs","-f","users"};
        srv.ParseCmdLine(6,cmdLine);
        auto result = srv.Initialize();
        CHECK(!result);
    }


}


SUITE(UsersBase){
    
    TEST(UsersBase_check_1){
        UsersBase usersBase;

        bool isHasException = false;
        try{
            usersBase.ParseFile("users");
        }
        catch(const char* what){
            isHasException = true;
        }
        CHECK(!isHasException);
    }

    TEST(UsersBase_check_nonReadable){
        UsersBase usersBase;
        CHECK_THROW(usersBase.ParseFile("users_nonReadable"),const char*);
    }

    TEST(UsersBase_check_empty){
        UsersBase usersBase;
        CHECK_THROW(usersBase.ParseFile("users_empty"),const char*);
    }

    TEST(UsersBase_check_ru){
        UsersBase usersBase;
        try{
            usersBase.ParseFile("users_ru");
        }
        catch(const char* what){
            std::cout<<"ERROR WHILE PARSING USERS FILE" << std::endl;
        }

        std::vector<std::pair<char*,const char*>> validUsers = {
            {"Привет","Мир"},
            {"ТЕСТ","123"},
        };

        bool result = true;

        for(const auto &user:validUsers){
            if(!usersBase.isHasUser(user.first)){
                result == false;
                break;
            }
            if(usersBase.getPassword(user.first) != user.second) {
                result == false;
                break;  
            }
        }

        CHECK(result);
    }
}

SUITE(Logger){
    TEST(logger_check_1){
        Logger logger;

        auto result = logger.Initialize("logs");
        CHECK(result);
    }

    TEST(logger_check_nonWriteable){
        Logger logger;

        auto result = logger.Initialize("logs_nonWriteable");
        CHECK(!result);
    }

    TEST(logger_check_nonReadable){
        Logger logger;

        auto result = logger.Initialize("logs_nonReadable");
        CHECK(result);
    }
}

int main() {
    RunSuite("Arguments");
    RunSuite("Server");
    RunSuite("UsersBase");
    RunSuite("Logger");
    return 0;
    
}