// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <sys/types.h>

#include <atomic>
#include <cstdio>
#include <cstring>
#include <string_view>
#include <iostream>

#include <fmt/format.h>
#include <hal/Extensions.h>

#include <hal/Ports.h>
#include <hal/simulation/PWMData.h>
#include <hal/simulation/CanData.h>

static std::atomic<bool> gCANConnected = false;

extern "C" {
#if defined(WIN32) || defined(_WIN32)
__declspec(dllexport)
#endif
    int HALSIM_InitExtension(void) {
  static bool once = false;

  if (once) {
    std::fputs("Error: cannot invoke HALSIM_InitExtension twice.\n", stderr);
    return -1;
  }
  once = true;

  std::puts("Linux Can Initializing.");

  HAL_RegisterExtension("linux_can", &gCANConnected);

  HAL_RegisterExtensionListener(
      nullptr, [](void*, const char* name, void* data) {
        std::puts("linux_can listener callback:");
        std::puts(name);
      });

  HALSIM_RegisterPWMInitializedCallback(0,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm init callback " << param << " " << 
	static_cast<bool>(value->data.v_boolean) << std::endl;
      }, (void*)0x100, true);
  HALSIM_RegisterPWMSpeedCallback(0,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm speed callback " << param << " " << 
	static_cast<double>(value->data.v_double) << std::endl;
      }, (void*)0x100, true);
  HALSIM_RegisterPWMPositionCallback(0,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm position callback " << param << " " << 
	static_cast<double>(value->data.v_double) << std::endl;
      }, (void*)0x100, true);
  HALSIM_RegisterPWMPulseMicrosecondCallback(0,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm pulse microsecond callback " << param << " " << 
	static_cast<int32_t>(value->data.v_int) << std::endl;
      }, (void*)0x100, true);
  HALSIM_RegisterPWMPeriodScaleCallback(0,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm period scale callback " << param << " " << 
	static_cast<int32_t>(value->data.v_int) << std::endl;
      }, (void*)0x100, true);
  HALSIM_RegisterPWMZeroLatchCallback(0,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm zero latch callback " << param << " " << 
	static_cast<bool>(value->data.v_boolean) << std::endl;
      }, (void*)0x100, true);

  HALSIM_RegisterPWMInitializedCallback(1,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm init callback " << param << " " << 
	static_cast<bool>(value->data.v_boolean) << std::endl;
      }, (void*)0x101, true);
  HALSIM_RegisterPWMSpeedCallback(1,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm speed callback " << param << " " << 
	static_cast<double>(value->data.v_double) << std::endl;
      }, (void*)0x101, true);
  HALSIM_RegisterPWMPositionCallback(1,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm position callback " << param << " " << 
	static_cast<double>(value->data.v_double) << std::endl;
      }, (void*)0x101, true);
  HALSIM_RegisterPWMPulseMicrosecondCallback(1,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm pulse microsecond callback " << param << " " << 
	static_cast<int32_t>(value->data.v_int) << std::endl;
      }, (void*)0x101, true);
  HALSIM_RegisterPWMPeriodScaleCallback(1,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm period scale callback " << param << " " << 
	static_cast<int32_t>(value->data.v_int) << std::endl;
      }, (void*)0x101, true);
  HALSIM_RegisterPWMZeroLatchCallback(1,
      [](const char* name, void* param, const struct HAL_Value* value) { 
        std::cout << "pwm zero latch callback " << param << " " << 
	static_cast<bool>(value->data.v_boolean) << std::endl;
      }, (void*)0x101, true);


  HALSIM_RegisterCanSendMessageCallback(
      [](const char* name, void* param,
         uint32_t messageID,
         const uint8_t* data,
         uint8_t dataSize, int32_t periodMs,
         int32_t* status) {
        std::cout << "can send message callback " << param << " " << messageID << " ";
	if(dataSize) std::cout << dataSize << " " << data << "data ";
	std::cout << std::endl;
      }, (void*) 0x269);

  HALSIM_RegisterCanReceiveMessageCallback(
      [](const char* name, void* param, uint32_t* messageID, 
	uint32_t messageIDMask, uint8_t* data, uint8_t* dataSize, 
	uint32_t* timeStamp, int32_t* status) {
        std::cout << "can recieve message callback " << messageID << " " << messageIDMask << " ";
	if(dataSize) std::cout << dataSize << " " << data << "data ";
	std::cout << std::endl;
      }, (void*) 0x269);



  std::puts("Linux Can Initialized!");
  return 0;
}
}  // extern "C"
