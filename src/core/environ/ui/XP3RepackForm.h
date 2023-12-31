#pragma once
#include <string>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <dispatch/dispatch.h>
extern "C" {
    #import <UIKit/UIKit.h>
    #import <objc/message.h>
}


void TVPProcessXP3Repack(const std::string &dir);
