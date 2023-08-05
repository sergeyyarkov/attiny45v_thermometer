#include "onewire.h"

#define DS18B20_CMD_CONVERTTEMP     0x44
#define DS18B20_CMD_RSCRATCHPAD     0xbe
#define DS18B20_CMD_WSCRATCHPAD     0x4e
#define DS18B20_CMD_CPSCRATCHPAD    0x48
#define DS18B20_CONST_FAMILY_CODE   0x28

#ifndef DSTEMPERATURE_H
#define	DSTEMPERATURE_H

typedef struct DallasSensor {
  uint8_t SCRATCHPAD[8];             // ОЗУ (T_LSB, T_MSB, TH/USER BYTE 1, TH/USER BYTE 2, CONFIG, RESERVED, RESERVED, RESERVED, CRC8)
  uint8_t ROM[8];                    // ПЗУ (код семейства, серийный код, CRC8)
  int16_t TEMPERATURE;               // Температура в градусах цельсия (целая часть)
  uint16_t TEMPERATURE_FRACTION;     // Дробная часть
} DallasSensor;

// TODO сделать чтобы все работало с несколькими датчиками а не с одним (выполнять команду skiprom если один датчик, иначе выбирать к какому датчику обращаться)

/**
 * Читает ОЗУ датчика
 * @param scratchpad - первые 8 байт.
 * @return "1" - если данные успешно прочитались, "0" - если данные искажены
 */
uint8_t DallasTemp_ReadScratchpad(uint8_t *scratchpad);

/**
 * Записывает данные в ОЗУ датчика
 * @param data - 3 байта
 */
void DallasTemp_WriteScratchpad(uint8_t *data);

/**
 * Перемещает данные из ОЗУ в EEPROM датчика
 * @return "1" - данные успешно записаны, "0" - если не было ответа от датчика
 */
uint8_t DallasTemp_CopyScratchpad(void);

/**
 * Отправляет команду для оцифровки температуры.
 * @return "1" - если команда отправлена, "0" - если не было ответа от датчика
 */
uint8_t DallasTemp_Convert(void);

/**
 * Задает разрешение АЦП датчика
 * Время оцифровки:
 *      - 12 бит - 750ms
 *      - 11 бит - 375ms
 *      - 10 бит - 187.5ms
 *      - 9  бит - 93.75ms
 * @param r - разрешение АЦП (от 9 до 12)
 */
void DallasTemp_SetResolution(DallasSensor *Sensor, uint8_t r);

/**
 * Получает оцифрованное значение датчика и конвертирует занчение в читаемый вид.
 * @param Sensor - датчика
 */
void DallasTemp_GetTemperature(DallasSensor *Sensor);

/**
 * Читает семейный код датчика и проверяет его правильность
 * @param Sensor - датчик
 * @return Возвращает "1" если имеются проблемы с датчиком иначе "0"
 */
uint8_t DallasTemp_CheckError(DallasSensor *Sensor);

#endif	/* DSTEMPERATURE_H */

