#include "support/color.h"

#include <utility>

#include "support/math.h"

#define INT_CLAMP(_V) static_cast<uint8_t>((_V) & 0xffu)
#define FLOAT_CLAMP(_V) INT_CLAMP(static_cast<uint32_t>(255.f * utils::clamp((_V), 0.f, 1.f)))

Color::Color() :
	_rgba{}
{}

Color::Color(int red, int green, int blue, int alpha) :
	_r{ INT_CLAMP(red) },
	_g{ INT_CLAMP(green) },
	_b{ INT_CLAMP(blue) },
	_a{ INT_CLAMP(alpha) }
{}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
	_r{ red },
	_g{ green },
	_b{ blue },
	_a{ alpha }
{}



Color::Color(float red, float green, float blue, float alpha) :
	_r{ FLOAT_CLAMP(red) },
	_g{ FLOAT_CLAMP(green) },
	_b{ FLOAT_CLAMP(blue) },
	_a{ FLOAT_CLAMP(alpha) }
{}



Color::Color(const vec4u& v) :
	Color{ INT_CLAMP(v.x), INT_CLAMP(v.y), INT_CLAMP(v.z), INT_CLAMP(v.w) }
{}

Color::Color(const vec4f& v) :
	Color{ v.x, v.y, v.z, v.w }
{}

Color::Color(const vec3u& v) :
	Color{ INT_CLAMP(v.x), INT_CLAMP(v.y), INT_CLAMP(v.z) }
{}

Color::Color(const vec3f& v) :
	Color{ v.x, v.y, v.z }
{}

Color::Color(uint32_t rgba) :
	_rgba{ rgba }
{}

Color::Color(const Color& c) :
	_rgba{ c._rgba }
{}

Color::Color(Color&& c) noexcept :
	_rgba{ std::move(c._rgba) }
{}


Color& Color::operator= (const Color& c)
{
	_rgba = c._rgba;
	return *this;
}

Color& Color::operator= (Color&& c) noexcept
{
	_rgba = std::move(c._rgba);
	return *this;
}

uint8_t& Color::operator[] (int index)
{
	switch (index)
	{
		default:
		case 0: return _r;
		case 1: return _g;
		case 2: return _b;
		case 3: return _a;
	}
}

const uint8_t& Color::operator[] (int index) const
{
	switch (index)
	{
		default:
		case 0: return _r;
		case 1: return _g;
		case 2: return _b;
		case 3: return _a;
	}
}

Color::operator vec4u() const { return { _r, _g, _b, _a }; }
Color::operator vec4f() const { return { _r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f }; }
Color::operator vec3u() const { return { _r, _g, _b }; }
Color::operator vec3f() const { return { _r / 255.f, _g / 255.f, _b / 255.f }; }


void Color::set(int red, int green, int blue, int alpha)
{
	_r = INT_CLAMP(red);
	_g = INT_CLAMP(green);
	_b = INT_CLAMP(blue);
	_a = INT_CLAMP(alpha);
}
void Color::set(int red, int green, int blue)
{
	_r = INT_CLAMP(red);
	_g = INT_CLAMP(green);
	_b = INT_CLAMP(blue);
}

void Color::set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	_r = red;
	_g = green;
	_b = blue;
	_a = alpha;
}

void Color::set(uint8_t red, uint8_t green, uint8_t blue)
{
	_r = red;
	_g = green;
	_b = blue;
}

void Color::set(float red, float green, float blue, float alpha)
{
	_r = FLOAT_CLAMP(red);
	_g = FLOAT_CLAMP(green);
	_b = FLOAT_CLAMP(blue);
	_a = FLOAT_CLAMP(alpha);
}

void Color::set(float red, float green, float blue)
{
	_r = FLOAT_CLAMP(red);
	_g = FLOAT_CLAMP(green);
	_b = FLOAT_CLAMP(blue);
}



Color operator* (const Color& c, float value)
{
	return {
		static_cast<uint8_t>(static_cast<uint32_t>(c.getRed() * value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getGreen() * value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getBlue() * value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getAlpha() * value) & 0xffu)
	};
}
Color operator/ (const Color& c, float value)
{
	return {
		static_cast<uint8_t>(static_cast<uint32_t>(c.getRed() / value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getGreen() / value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getBlue() / value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getAlpha() / value) & 0xffu)
	};
}

Color& operator*= (Color& c, float value)
{
	c.set(
		static_cast<uint8_t>(static_cast<uint32_t>(c.getRed() * value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getGreen() * value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getBlue() * value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getAlpha() * value) & 0xffu)
	);
	return c;
}
Color& operator/= (Color& c, float value)
{
	c.set(
		static_cast<uint8_t>(static_cast<uint32_t>(c.getRed() / value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getGreen() / value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getBlue() / value) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c.getAlpha() / value) & 0xffu)
	);
	return c;
}

Color operator+ (const Color& c0, const Color& c1)
{
	return {
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getRed() + c1.getRed()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getGreen() + c1.getGreen()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getBlue() + c1.getBlue()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getAlpha() + c1.getAlpha()) & 0xffu)
	};
}
Color operator- (const Color& c0, const Color& c1)
{
	return {
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getRed() - c1.getRed()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getGreen() - c1.getGreen()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getBlue() - c1.getBlue()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getAlpha() - c1.getAlpha()) & 0xffu)
	};
}

Color& operator+= (Color& c0, const Color& c1)
{
	c0.set(
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getRed() + c1.getRed()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getGreen() + c1.getGreen()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getBlue() + c1.getBlue()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getAlpha() + c1.getAlpha()) & 0xffu)
	);
	return c0;
}
Color& operator-= (Color& c0, const Color& c1)
{
	c0.set(
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getRed() - c1.getRed()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getGreen() - c1.getGreen()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getBlue() - c1.getBlue()) & 0xffu),
		static_cast<uint8_t>(static_cast<uint32_t>(c0.getAlpha() - c1.getAlpha()) & 0xffu)
	);
	return c0;
}






const Color Color::BLACK{ 0, 0, 0 };
const Color Color::WHITE{ 255, 255, 255 };
const Color Color::GRAY{ 64, 64, 64 };
const Color Color::RED{ 255, 0, 0 };
const Color Color::GREEN{ 0, 255, 0 };
const Color Color::BLUE{ 0, 0, 255 };
const Color Color::YELLOW{ 255, 255, 0 };
const Color Color::CYAN{ 0, 255, 255 };
const Color Color::PURPLE{ 255, 0, 255 };
