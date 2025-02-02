/*
 * Copyright (c) 2016-2022 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * \file arm_uart_drv.h
 * \brief Generic driver for ARM UART.
 */

#ifndef __ARM_UART_DRV_H__
#define __ARM_UART_DRV_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ARM UART device configuration structure */
struct arm_uart_dev_cfg_t {
	const uint32_t base;              /*!< UART base address */
	const uint32_t default_baudrate;  /*!< Default baudrate */
};

/* ARM UART device data structure */
struct arm_uart_dev_data_t {
	uint32_t state;       /*!< Indicates if the uart driver
                               is initialized and enabled */
	uint32_t system_clk;  /*!< System clock */
	uint32_t baudrate;    /*!< Baudrate */
};

/* ARM UART device structure */
struct arm_uart_dev_t {
	const struct arm_uart_dev_cfg_t *const cfg;  /*!< UART configuration */
	struct arm_uart_dev_data_t *const data;      /*!< UART data */
};

/* ARM UART enumeration types */
enum arm_uart_error_t {
	ARM_UART_ERR_NONE = 0,      /*!< No error */
	ARM_UART_ERR_INVALID_ARG,   /*!< Error invalid input argument */
	ARM_UART_ERR_INVALID_BAUD,  /*!< Invalid baudrate */
	ARM_UART_ERR_NOT_INIT,      /*!< Error UART not initialized */
	ARM_UART_ERR_NOT_READY,     /*!< Error UART not ready */
};

enum arm_uart_irq_t {
	ARM_UART_IRQ_RX,       /*!< RX interrupt source */
	ARM_UART_IRQ_TX,       /*!< TX interrupt source */
	ARM_UART_IRQ_COMBINED  /*!< RX-TX combined interrupt source */
};

/**
 * \brief Initializes UART. It uses the default baudrate to configure
 * the peripheral at this point.
 *
 * \param[in] dev         UART device struct \ref arm_uart_dev_t
 * \param[in] system_clk  System clock used by the device.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_init(struct arm_uart_dev_t *dev,
									uint32_t system_clk);

/**
 * \brief Sets the UART baudrate.
 *
 * \param[in] dev       UART device struct \ref arm_uart_dev_t
 * \param[in] baudrate  New baudrate.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_set_baudrate(struct arm_uart_dev_t *dev,
		uint32_t baudrate);

/**
 * \brief Gets the UART baudrate.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns the UART baudrate.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t arm_uart_get_baudrate(struct arm_uart_dev_t *dev);

/**
 * \brief Sets system clock.
 *
 * \param[in] dev         UART device struct \ref arm_uart_dev_t
 * \param[in] system_clk  System clock used by the device.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_set_clock(struct arm_uart_dev_t *dev,
		uint32_t system_clk);
/**
 * \brief Reads one byte from UART dev.
 *
 * \param[in] dev   UART device struct \ref arm_uart_dev_t
 * \param[in] byte  Pointer to byte.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note For better performance, this function doesn't check if dev and byte
 * pointer are NULL, and if the driver is initialized.
 */
enum arm_uart_error_t arm_uart_read(struct arm_uart_dev_t *dev, uint8_t *byte);

/**
 * \brief Writes a byte to UART dev.
 *
 * \param[in] dev   UART device struct \ref arm_uart_dev_t
 * \param[in] byte  Byte to write.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note For better performance, this function doesn't check if dev is NULL and
 * if the driver is initialized to have better performance.
 */
enum arm_uart_error_t arm_uart_write(struct arm_uart_dev_t *dev, uint8_t byte);

/**
 * \brief Enables TX interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_irq_tx_enable(struct arm_uart_dev_t *dev);

/**
 * \brief Disables TX interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_irq_tx_disable(struct arm_uart_dev_t *dev);

/**
 * \brief  Verifies if Tx is ready to send more data.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return  1 if TX is ready, 0 otherwise.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t arm_uart_tx_ready(struct arm_uart_dev_t *dev);

/**
 * \brief Enables RX interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_irq_rx_enable(struct arm_uart_dev_t *dev);

/**
 * \brief Disables RX interrupt
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_irq_rx_disable(struct arm_uart_dev_t *dev);

/**
 * \brief Verifies if Rx has data.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return 1 if RX has data, 0 otherwise.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t arm_uart_rx_ready(struct arm_uart_dev_t *dev);

/**
 * \brief Clears UART interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 * \param[in] irq  IRQ source to clean \ref arm_uart_irq_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_clear_interrupt(struct arm_uart_dev_t *dev,
							  enum arm_uart_irq_t irq);

/**
 * \brief Enables TX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_tx_enable(struct arm_uart_dev_t *dev);

/**
 * \brief Disables TX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_tx_disable(struct arm_uart_dev_t *dev);

/**
 * \brief Enables RX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_rx_enable(struct arm_uart_dev_t *dev);

/**
 * \brief Disables RX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_rx_disable(struct arm_uart_dev_t *dev);

#ifdef __cplusplus
}
#endif
#endif /* __ARM_UART_DRV_H__ */
