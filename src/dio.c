#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "dio_init.h"
#include "dio_reg.h"

/* IO Pins */
void DIO_SetPinValue(unsigned char port, unsigned char PinId, unsigned char PinVal)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((port <= PORT_D) && (PinId <= PIN_7))
	{
		if (PinVal == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (port)
			{
			case PORT_B:
				SET_BIT(PORTB_Register, PinId);
				break;
			case PORT_C:
				SET_BIT(PORTC_Register, PinId);
				break;
			case PORT_D:
				SET_BIT(PORTD_Register, PinId);
				break;
			}
		}

		else if (PinVal == LOW)
		{
			/* Check on the Required PORT Number */
			switch (port)
			{
			case PORT_B:
				CLR_BIT(PORTB_Register, PinId);
				break;
			case PORT_C:
				CLR_BIT(PORTC_Register, PinId);
				break;
			case PORT_D:
				CLR_BIT(PORTD_Register, PinId);
				break;
			}
		}

		else
		{
			/* Do nothing, Wrong value to set */
		}
	}

	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

unsigned char DIO_GetPinValue(unsigned char port, unsigned char PinId)
{
	/* Define Local Variable to get the BIT Value */
	unsigned char result;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((port <= PORT_D) && (PinId <= PIN_7))
	{
		/* Check on the Required PORT Number */
		switch (port)
		{

		case PORT_B:
			result = GET_BIT(PINB_Register, PinId);
			break;
		case PORT_C:
			result = GET_BIT(PINC_Register, PinId);
			break;
		case PORT_D:
			result = GET_BIT(PIND_Register, PinId);
			break;
		}
	}

	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		result = 0xFF;
	}

	return result;
}

void DIO_SetPinDirection(unsigned char port, unsigned char PinId, unsigned char PinDir)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((port <= PORT_D) && (PinId <= PIN_7))
	{
		if (PinDir == OUTPUT)
		{
			/* Check on the Required PORT Number */
			switch (port)
			{

			case PORT_B:
				SET_BIT(DDRB_Register, PinId);
				break;
			case PORT_C:
				SET_BIT(DDRC_Register, PinId);
				break;
			case PORT_D:
				SET_BIT(DDRD_Register, PinId);
				break;
			}
		}

		else if (PinDir == INPUT)
		{
			/* Check on the Required PORT Number */
			switch (port)
			{

			case PORT_B:
				CLR_BIT(DDRB_Register, PinId);
				break;
			case PORT_C:
				CLR_BIT(DDRC_Register, PinId);
				break;
			case PORT_D:
				CLR_BIT(DDRD_Register, PinId);
				break;
			}
		}

		else
		{
			/* Do nothing, Wrong Direction Required */
		}
	}

	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

/* IO Ports */
void DIO_SetPortDirection(unsigned char Port, unsigned char PortDir)
{
	/* Check on the Required PORT Number */
	switch (Port)
	{

	case PORT_B:
		DDRB_Register = PortDir;
		break;
	case PORT_C:
		DDRC_Register = PortDir;
		break;
	case PORT_D:
		DDRD_Register = PortDir;
		break;
	default: /* Wrong Port ID */
		break;
	}
}

void DIO_SetPortValue(unsigned char Port, unsigned char PortVal)
{
	/* Check on the Required PORT Number */
	switch (Port)
	{

	case PORT_B:
		PORTB_Register = PortVal;
		break;
	case PORT_C:
		PORTC_Register = PortVal;
		break;
	case PORT_D:
		PORTD_Register = PortVal;
		break;
	default: /* Wrong Port ID */
		break;
	}
}
