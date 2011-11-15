call lint.bat --R Ripple
call lint.bat --R RippleLibrary
call lint.bat TestClientTest/Main.cpp
call lint.bat TestFramework/Main.cpp
call lint.bat TestFramework/MessageHandlerTest.cpp
call lint.bat TestFramework/MessageHandlerTest.h
call lint.bat TestFramework/MessageSignalSpy.h
call lint.bat TestFramework/QtStageWebViewTest.cpp
call lint.bat TestFramework/QtStageWebViewTest.h
exit(1)





