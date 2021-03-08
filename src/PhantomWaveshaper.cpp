/*
  ==============================================================================

    PhantomWaveshaper.cpp
    Created: 02 Feb 2021 23:02:00
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomWaveshaper.h"

//==============================================================================
PhantomWaveshaper::PhantomWaveshaper()
{

}

PhantomWaveshaper::~PhantomWaveshaper()
{

}

//==============================================================================
float PhantomWaveshaper::fexp2(float x) noexcept
{
    float s = sign(-x);
    float t1 = 1.0f - std::expf(std::abs(x));
    float t2 = MathConstants<float>::euler - 1.0f;

    return s * t1 / t2;
}

float PhantomWaveshaper::atsr(float x) noexcept
{
    float t1 = 2.5f * std::atanf(0.9f * x);
    float t2 = 2.5f * std::sqrtf(1.0f - std::powf(0.9f * x, 2.0f));

    return t1 + t2 - 2.5f;
}

float PhantomWaveshaper::cube(float x) noexcept
{
    return x * x * x;
}

float PhantomWaveshaper::htan(float k, float x) noexcept
{
    return std::tanhf(k * x);
}

float PhantomWaveshaper::hclip(float x) noexcept
{
    return std::abs(x) > 0.5f ? 0.5f * sign(x) : x;
}

//==============================================================================
float PhantomWaveshaper::clip(float x, float lower, float upper) noexcept
{
    return std::max(lower, std::min(x, upper));
}

float PhantomWaveshaper::sign(float x) noexcept
{
    return x >= 0.0f ? 1.0f : -1.0f;
}
