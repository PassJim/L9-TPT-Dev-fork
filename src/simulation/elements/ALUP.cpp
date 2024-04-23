#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_ALUP()
{
	Identifier = "DEFAULT_PT_ALUP";
	Name = "ALUP";
	Colour = 0xA1A19E_rgb;
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.3f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 2;
	Hardness = 2;

	Weight = 90;

	HeatConduct = 211;
	Description = "Broken metal. Created when iron rusts or when metals break from pressure.";

	Properties = TYPE_PART|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1220.0f;
	HighTemperatureTransition = PT_ALUM;

	Update = &update;
	Graphics = &graphics;
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 523.15f)//250.0f+273.15f
	{
		auto tempFactor = int(1000 - ((523.15f-parts[i].temp)*2));
		if(tempFactor < 2)
			tempFactor = 2;
		for (auto rx = -1; rx <= 1; rx++)
		{
			for (auto ry = -1; ry <= 1; ry++)
			{
				if (rx || ry)
				{
					auto r = pmap[y+ry][x+rx];
					if (!r)
						continue;
					if (TYP(r)==PT_BREC && sim->rng.chance(1, tempFactor))
					{
						if (sim->rng.chance(1, 2))
						{
							sim->create_part(ID(r), x+rx, y+ry, PT_THRM);
						}
						else
							sim->create_part(i, x, y, PT_THRM);
					}
				}
			}
		}
	}
	return 0;
}
static int graphics(GRAPHICS_FUNC_ARGS)
{
	int z = (cpart->tmp2 - 2) * 8;
	*colr += z;
	*colg += z;
	*colb += z;
	return 0;
}
static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	sim->parts[i].tmp2 = sim->rng.between(0, 4);
}

