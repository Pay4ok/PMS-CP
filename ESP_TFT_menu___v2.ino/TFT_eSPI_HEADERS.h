#include <mutex>
#include "SPI.h"
#include "TFT_eSPI.h"

#ifndef TFT_eSPI_HEADERS
#define TFT_eSPI_HEADERS

// Определение глобального мьютекса
extern std::mutex tftMutex;
extern TFT_eSPI tft; // Invoke library

#endif
