/**
 * @file       led.h
 * @version    0.0.1
 * @date       2022-08-1
 * @author     Vu Tran
 */
/* Define ------------------------------------------------------------*/
#ifndef __LED_H
#define __LED_H
#ifdef __cplusplus
extern "C"
{
#endif
#define     __IOV    volatile             /*!< Defines 'read / write' permissions */
/*************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "stm32f4xx_hal.h"
/*****************************************************************************/
/**
 * @brief General Purpose I/O
 */

typedef struct
{
  __IOV uint32_t MODER;   /*!< GPIO port mode register,               Address offset: 0x00      */
  __IOV uint32_t OTYPER;  /*!< GPIO port output type register,        Address offset: 0x04      */
  __IOV uint32_t OSPEEDR; /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IOV uint32_t PUPDR;   /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IOV uint32_t IDR;     /*!< GPIO port input data register,         Address offset: 0x10      */
  __IOV uint32_t ODR;     /*!< GPIO port output data register,        Address offset: 0x14      */
  __IOV uint32_t BSRR;    /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  __IOV uint32_t LCKR;    /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IOV uint32_t AFR[2];  /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} gpio_type_t;
  /**
   * @brief Status of Led API
   */
  typedef enum
  {
    LED_STATUS_OK = 0,
    LED_STATUS_ERROR_OPTION,
    LED_STATUS_ERROR_NULL_PTR
  } led_status_t;
  /**
   * @brief Value of Led
   */
  typedef enum
  {
    LED_VALUE_OFF = 0, /**< LED Turn off */
    LED_VALUE_ON = 1   /**< LED Turn on */
  } led_value_t;
  /* Public structure  ----------------------------------------- */
  /**
   * @brief <Led init gpio>
   */
  typedef struct
  {
    gpio_type_t *gpio_port;
    uint16_t gpio_pin;
    led_value_t value;
  } led_t;
  /**
   * @brief Mode of Led
   */
  typedef enum
  {
    LED_ENABLE_LOW, /**<Led is enable when led pin is LOW */
    LED_ENABLE_HIGH /**<Led is enable when led pin is HIGH */
  } led_enable_logic_t;

  /* Public function prototypes ----------------------------------------- */
  /**
   * @brief  <Control led>
   *
   * @param[in]     <GPIOx, GPIO_Pin>
   * @param[out]    <SetPin led>
   *
   * @attention  <HAL_GPIO>
   *
   * @return
   *  - 0: //write low
   *  - 1: //write high
   */
  /*******************************************************************************
   * FUNCTIONS - API
   ******************************************************************************/
  /*!
   *******************************************************************************
   * @fn       led_status_t init_led(led_t *led, gpio_type_t *gpio_port, uint16_t gpio_pin);
   *
   * @brief   Init info for LED
   *
   * @param   led            - handle for led
   * @param   gpio_port          - Led gpio_port
   * @param   gpio_pin       - Led gpio_pin
   *
   * @return 	LED_STATUS_OK
   * @return  LED_STATUS_ERROR_OPTION
   * @return 	LED_STATUS_ERROR_NULL_PTR
   ******************************************************************************/
  led_status_t init_led(led_t *led, gpio_type_t *gpio_port, uint16_t gpio_pin); // init pin led
  /*!
   *******************************************************************************
   * @fn      led_status_t configure_led_pins(led_t *led);
   *
   * @brief   The configuration pin led depend on HAL_GPIO API
   *
   * @param   led            - handle for led
   *
   * @return 	LED_STATUS_OK
   * @return  LED_STATUS_ERROR_OPTION
   * @return 	LED_STATUS_ERROR_NULL_PTR
   ******************************************************************************/
  led_status_t configure_led_pins(led_t *led); // config led pin
  /*!
   *******************************************************************************
   * @fn      led_turn_off(led_t *led);
   *
   * @brief   The fuction handle led off
   *
   * @param   led            - handle for led
   * @return 	LED_STATUS_OK
   * @return  LED_STATUS_ERROR_OPTION
   * @return 	LED_STATUS_ERROR_NULL_PTR
   ******************************************************************************/
  led_status_t led_turn_off(led_t *led); // turn off led
  /*!
   *******************************************************************************
   * @fn      led_turn_off(led_t *led);
   *
   * @brief   The fuction handle led on
   *
   * @param   led            - handle for led
   * @return 	LED_STATUS_OK
   * @return  LED_STATUS_ERROR_OPTION
   * @return 	LED_STATUS_ERROR_NULL_PTR
   ******************************************************************************/
  led_status_t led_turn_on(led_t *led); // turn on led
  /*!
   *******************************************************************************
   * @fn      led_toggle(led_t *led);
   *
   * @brief   The fuction handle toggle status led
   *
   * @param   led            - handle for led
   * @return 	LED_STATUS_OK
   * @return  LED_STATUS_ERROR_OPTION
   * @return 	LED_STATUS_ERROR_NULL_PTR
   ******************************************************************************/
  led_status_t led_toggle(led_t *led); // toggle led
/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* LED_H_ */
/* End of file -------------------------------------------------------- */
