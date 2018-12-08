#ifndef COLORSENSOR_H
#define COLORSENSOR_H

/**
 * Initializes the EV3 colorsensor
 */
uint8_t colorsensor_init(void);

/**
 * Returns wether the colorsensor detects darkness or not.
 *
 * @returns true for darkness false for light
 */
bool colorsensor_darkness(void);

#endif
