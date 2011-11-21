#!/bin/bash
sh lint.sh --R Ripple
sh lint.sh --R RippleLibrary
sh lint.sh TestClientTest/Main.cpp
sh lint.sh TestFramework/Main.cpp
sh lint.sh TestFramework/MessageHandlerTest.cpp
sh lint.sh TestFramework/MessageHandlerTest.h
sh lint.sh TestFramework/MessageSignalSpy.h
sh lint.sh TestFramework/QtStageWebViewTest.cpp
sh lint.sh TestFramework/QtStageWebViewTest.h
sh lint.sh TestFramework/NetworkAccessManagerTest.cpp
sh lint.sh TestFramework/NetworkAccessManagerTest.h
sh lint.sh TestFramework/ResourceRequestedReplyTest.cpp
sh lint.sh TestFramework/ResourceRequestedReplyTest.h
