@echo off
call lint.bat --R Ripple
if errorlevel 1 exit 1
call lint.bat --R RippleLibrary
if errorlevel 1 exit 1
call lint.bat TestClientTest/Main.cpp
if errorlevel 1 exit 1
call lint.bat TestFramework/Main.cpp
if errorlevel 1 exit 1
call lint.bat TestFramework/MessageHandlerTest.cpp
if errorlevel 1 exit 1
call lint.bat TestFramework/MessageHandlerTest.h
if errorlevel 1 exit 1
call lint.bat TestFramework/MessageSignalSpy.h
if errorlevel 1 exit 1
call lint.bat TestFramework/QtStageWebViewTest.cpp
if errorlevel 1 exit 1
call lint.bat TestFramework/QtStageWebViewTest.h
if errorlevel 1 exit 1
@echo on




