#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_HLOY()
{
	Identifier = "DEFAULT_PT_HLOY";
	Name = "HLOY";
	Colour = 0xFF804633_rgb;
	MenuVisible = 1;
	MenuSection = SC_MOD;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "Human Alloy Metal, brittle, shatters under pressure";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 1.0f;
	HighPressureTransition = ST;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1273.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
		for (auto rx = -1; rx <= 1; rx++)
	{
		for (auto ry = -1; ry <= 1; ry++)
		{
			if (rx || ry)
			{
				auto r = pmap[y+ry][x+rx];
				switch (TYP(r))
				{
			
				//converts Metals
				case PT_BRMT:
					if (sim->rng.chance(1, 2000))
						sim->create_part(ID(r),x+rx,y+ry,PT_HLOY);
					break;
				
				}
			}
		}

	}
	

		if (parts[i].tmp>1)
		{
			parts[i].tmp--;
			for (auto rx = -1; rx <= 1; rx++)
			{
				for (auto ry = -1; ry <= 1; ry++)
				{
					if (rx || ry)
					{
						auto r = pmap[y+ry][x+rx];
						if (!r)
							continue;
						if ((TYP(r)==PT_METL || TYP(r)==PT_IRON) && sim->rng.chance(1, 100))
						{
							sim->part_change_type(ID(r),x+rx,y+ry,PT_BMTL);
							parts[ID(r)].tmp = (parts[i].tmp<=7) ? parts[i].tmp=1 : parts[i].tmp - sim->rng.between(0, 4);
						}
					}
				}
			}
		}
		else if (parts[i].tmp==1 && sim->rng.chance(1, 1000))
		{
			parts[i].tmp = 0;
			sim->part_change_type(i,x,y,PT_BRMT);
		}
		return 0;
}
