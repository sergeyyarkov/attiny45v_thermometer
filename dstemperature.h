#include "onewire.h"

#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe

#ifndef DSTEMPERATURE_H
#define	DSTEMPERATURE_H

typedef struct DallasSensor {
  uint8_t SCRATCHPAD[8];            // ОЗУ
  uint8_t ROM[8];                   // ПЗУ
  int16_t TEMPERATURE;              // Температура в градусах цельсия (целая часть)
  uint8_t TEMPERATURE_FRACTION;     // Дробная часть
} DallasSensor;

/**
 * Читает ОЗУ датчика
 * @param scratchpad - первые 8 байт.
 * @return "1" - если данные успешно прочитались, "0" - если данные искажены
 */
uint8_t DallasTemp_ReadScratchpad(uint8_t *scratchpad);

/**
 * Отправляет команду для оцифровки температуры.
 * @return "1" - если команда отправлена, "0" - если не было ответа от датчика
 */
uint8_t DallasTemp_Convert(void);

/**
 * Получает оцифрованное значение датчика и конвертирует занчение в читаемый вид.
 * @param Sensor - структура датчика
 */
void DallasTemp_GetTemperature(DallasSensor *Sensor);

#endif	/* DSTEMPERATURE_H */

