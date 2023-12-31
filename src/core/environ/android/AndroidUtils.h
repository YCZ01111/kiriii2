#pragma once
#include <jni.h>
#include <string>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <dispatch/dispatch.h>
extern "C" {
    #import <UIKit/UIKit.h>
    #import <objc/message.h>
}


std::string TVPGetDeviceID();
