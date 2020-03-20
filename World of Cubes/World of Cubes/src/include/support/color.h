#pragma once

#include <cstdint>

#include "vectors.h"

class Color
{
private:
	union
	{
		struct
		{
			uint8_t _r;
			uint8_t _g;
			uint8_t _b;
			uint8_t _a;
		};
		uint32_t _rgba;
	};

public:
	Color();

	Color(int red, int green, int blue, int alpha = 255);
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
	Color(float red, float green, float blue, float alpha = 1.f);

	explicit Color(const vec4u& v);
	explicit Color(const vec4f& v);
	explicit Color(const vec3u& v);
	explicit Color(const vec3f& v);
	explicit Color(uint32_t rgba);

	Color(const Color& c);
	Color(Color&& c) noexcept;


	Color& operator= (const Color& c);
	Color& operator= (Color&& c) noexcept;


	uint8_t& operator[] (int index);
	const uint8_t& operator[] (int index) const;


	explicit operator vec4u() const;
	explicit operator vec4f() const;
	explicit operator vec3u() const;
	explicit operator vec3f() const;


	void set(int red, int green, int blue, int alpha);
	void set(int red, int green, int blue);

	void set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	void set(uint8_t red, uint8_t green, uint8_t blue);

	void set(float red, float green, float blue, float alpha);
	void set(float red, float green, float blue);

	
	inline uint8_t getRed() const { return _r; }
	inline uint8_t getGreen() const { return _g; }
	inline uint8_t getBlue() const { return _b; }
	inline uint8_t getAlpha() const { return _a; }

	inline void setRed(uint8_t value) { _r = value; }
	inline void setGreen(uint8_t value) { _g = value; }
	inline void setBlue(uint8_t value) { _b = value; }
	inline void setAlpha(uint8_t value) { _a = value; }

	inline float getRedProportion() const { return _r / 255.f; }
	inline float getGreenProportion() const { return _g / 255.f; }
	inline float getBlueProportion() const { return _b / 255.f; }
	inline float getAlphaProportion() const { return _a / 255.f; }

	inline void setRedProportion(float value) { _r = static_cast<uint8_t>(static_cast<uint32_t>(255.f * utils::clamp(value, 0.f, 1.f)) & 0xffu); }
	inline void setGreenProportion(float value) { _g = static_cast<uint8_t>(static_cast<uint32_t>(255.f * utils::clamp(value, 0.f, 1.f)) & 0xffu); }
	inline void setBlueProportion(float value) { _b = static_cast<uint8_t>(static_cast<uint32_t>(255.f * utils::clamp(value, 0.f, 1.f)) & 0xffu); }
	inline void setAlphaProportion(float value) { _a = static_cast<uint8_t>(static_cast<uint32_t>(255.f * utils::clamp(value, 0.f, 1.f)) & 0xffu); }

	inline void set(const vec4u& v) { set(static_cast<uint8_t>(v.x & 0xffu), static_cast<uint8_t>(v.y & 0xffu), static_cast<uint8_t>(v.z & 0xffu), static_cast<uint8_t>(v.w & 0xffu)); }
	inline void set(const vec3u& v) { set(static_cast<uint8_t>(v.x & 0xffu), static_cast<uint8_t>(v.y & 0xffu), static_cast<uint8_t>(v.z & 0xffu)); }

	inline void set(const vec4f& v) { set(v.x, v.y, v.z, v.w); }
	inline void set(const vec3f& v) { set(v.x, v.y, v.z); }

	inline uint32_t rgb() const { return _rgba & 0xffffffu; }
	inline uint32_t rgba() const { return _rgba; }
	inline void rgba(uint32_t value) { _rgba = value; }

	inline uint32_t* data() { return &_rgba; }
	inline const uint32_t* data() const { return &_rgba; }

	inline uint32_t& operator* () { return _rgba; }
	inline const uint32_t& operator* () const { return _rgba; }

	static const Color WHITE;
	static const Color BLACK;
	static const Color GRAY;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color CYAN;
	static const Color YELLOW;
	static const Color PURPLE;
};


Color operator* (const Color& c, float value);
Color operator/ (const Color& c, float value);

Color& operator*= (Color& c, float value);
Color& operator/= (Color& c, float value);

Color operator+ (const Color& c0, const Color& c1);
Color operator- (const Color& c0, const Color& c1);

Color& operator+= (Color& c0, const Color& c1);
Color& operator-= (Color& c0, const Color& c1);

