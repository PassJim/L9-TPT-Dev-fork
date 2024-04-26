#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_YFUL()
{
	Identifier = "DEFAULT_PT_YFUL";
	Name = "YFUL"; 
	Colour = 0xFFAA7AD2_rgb;
	MenuVisible = 1;
	MenuSection = SC_MOD;
	Enabled = 1;

	Advection = 0.5f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.92f;
	Loss = 0.97f;
	Collision = 0.0f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 500;
	Explosive = 2;
	Meltable = 0;
	Hardness = 3;
	PhotonReflectWavelengths = 0x0007C000;

	Weight = 23;

	HeatConduct = 50;
	Description = "Y-Fuel, used to fuel spaceships, less combustable";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 605.0f;
	HighTemperatureTransition = PT_FIRE;

		Update = &update;
		Graphics = &graphics;
		Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	for (auto rx = -2; rx <= 2; rx++)
	{
		for (auto ry = -2; ry <= 2; ry++)
		{
			if (rx || ry)
			{
				auto r = pmap[y+ry][x+rx];
				switch (TYP(r))
				{
			
				//converts liquids into itself
				case PT_NITR:
					if (sim->rng.chance(1, 500))
						sim->create_part(ID(r),x+rx,y+ry,PT_YFUL);
					break;
				// corrodes the following
				case PT_BMTL:
				if (sim->rng.chance(1, 100))
					sim->create_part(ID(r),x+rx,y+ry,PT_BRMT);
				break;
				case PT_METL:
				if (sim->rng.chance(1, 100))
					sim->create_part(ID(r),x+rx,y+ry,PT_BRMT);
				break;
				case PT_IRON:
				if (sim->rng.chance(1, 100))
					sim->create_part(ID(r),x+rx,y+ry,PT_BRMT);
				break;
				case PT_BRMT:
				if (sim->rng.chance(1, 500))
					sim->kill_part(ID(r));
				break;
				//dissolves the following 
				case PT_INSL:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_YFUL);
					break;
				case PT_PSCN:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_YFUL);
					break;
				case PT_CRAY:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_YFUL);
					break;
				case PT_FRAY:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_YFUL);
					break;
				case PT_NSCN:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_YFUL);
					break;
				// Calcifies solids into coal
				case PT_PLNT:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_COAL);
						
					break;
				case PT_BANG:
					if (sim->rng.chance(1, 100))
						
						sim->create_part(ID(r),x+rx,y+ry,PT_COAL);
						
					break;
				case PT_WOOD:
					if (sim->rng.chance(1, 100))
						
						sim->create_part(ID(r),x+rx,y+ry,PT_COAL);
						
					break;
				
				default:
					continue;
				}
			}
		}
	}
	return 0;

	
		

}
static int graphics(GRAPHICS_FUNC_ARGS)
{	
	*pixel_mode |=PMODE_FLARE;
	int z = (cpart->tmp - 5) * 16;//speckles!
	*colr += z;
	*colg += z;
	*colb += z;
	return 0;
}
static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	sim->parts[i].tmp = sim->rng.between(0, 4);
}
