#include "pch.h"

#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include "App.h"

#pragma comment(lib, "wbemuuid.lib")

int main(int argc, char** argv)
{
    App app;
    app.run();



    return 0;

}