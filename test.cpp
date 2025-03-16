import std; 

#include "types.h"
#include "float.h"
#include "base.h"
#include "vector.h"
#include "matrix.h"

#include <Windows.h>

int main(int argc, char** argv)
{
#define VALIDATION_ERROR(x) MessageBoxA(NULL, x, "Validation Error", MB_OK)

#pragma region VECTOR_VALIDATION
	if (fx::broadcast(1.0f) != fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f })
	{
		VALIDATION_ERROR("broadcast(1)");
		return -1;
	}

	else if (fx::broadcast(2.0f) != fx::vec4{ 2.0f, 2.0f, 2.0f, 2.0f })
	{
		VALIDATION_ERROR("broadcast(2)");
		return 1;
	}


	else if (fx::truncate(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != fx::vec3{ 1.0f, 1.0f, 1.0f })
	{
		VALIDATION_ERROR("truncate({ 1, 1, 1, 1 })");
		return 2;
	}

	else if (fx::truncate(fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != fx::vec3{ 1.0f, 2.0f, 3.0f })
	{
		VALIDATION_ERROR("truncate({ 1, 2, 3, 4 })");
		return 3;
	}


	else if (fx::extend(fx::vec3{ 1.0f, 2.0f, 3.0f }) != fx::vec4{ 1.0f, 2.0f, 3.0f, 1.0f })
	{
		VALIDATION_ERROR("extend({ 1, 2, 3 })");
		return 4;
	}

	else if (fx::extend(fx::vec3{ 2.0f, 3.0f, 4.0f }) != fx::vec4{ 2.0f, 3.0f, 4.0f, 1.0f })
	{
		VALIDATION_ERROR("extend({ 2, 3, 4 })");
		return 5;
	}


	else if (fx::scale(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 2.0f) != fx::vec4{ 2.0f, 2.0f, 2.0f, 2.0f })
	{
		VALIDATION_ERROR("scale({ 1, 1, 1, 1 }, 2)");
		return 6;
	}

	else if (fx::scale(fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, 2.0f) != fx::vec4{ 2.0f, 4.0f, 6.0f, 8.0f })
	{
		VALIDATION_ERROR("scale({ 1, 2, 3, 4 }, 2)");
		return 7;
	}


	else if (fx::invert(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != fx::vec4{ -1.0f, -1.0f, -1.0f, -1.0f })
	{
		VALIDATION_ERROR("invert({ 1, 1, 1, 1 })");
		return 8;
	}

	else if (fx::invert(fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != fx::vec4{ -1.0f, -2.0f, -3.0f, -4.0f })
	{
		VALIDATION_ERROR("invert({ 1, 2, 3, 4 })");
		return 9;
	}


	else if (fx::add(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
					 fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != fx::vec4{ 2.0f, 3.0f, 4.0f, 5.0f })
	{
		VALIDATION_ERROR("add({ 1, 1, 1, 1 }, { 1, 2, 3, 4 })");
		return 10;
	}

	else if (fx::add(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
					 fx::vec4{ 2.0f, 3.0f, 4.0f, 5.0f }) != fx::vec4{ 3.0f, 4.0f, 5.0f, 6.0f })
	{
		VALIDATION_ERROR("add({ 1, 1, 1, 1 }, { 2, 3, 4, 5 })");
		return 11;
	}


	else if (fx::subtract(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
						  fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != fx::vec4{ 0.0f, -1.0f, -2.0f, -3.0f })
	{
		VALIDATION_ERROR("subtract({ 1, 1, 1, 1 }, { 1, 2, 3, 4 })");
		return 12;
	}

	else if (fx::subtract(fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f },
						  fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != fx::vec4{ 0.0f, 1.0f, 2.0f, 3.0f })
	{
		VALIDATION_ERROR("subtract({ 1, 2, 3, 4 }, { 1, 1, 1, 1 })");
		return 13;
	}


	else if (fx::multiply(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
						  fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f })
	{
		VALIDATION_ERROR("multiply({ 1, 1, 1, 1 }, { 1, 2, 3, 4 })");
		return 14;
	}

	else if (fx::multiply(fx::vec4{ 2.0f, 2.0f, 2.0f, 2.0f },
						  fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != fx::vec4{ 2.0f, 4.0f, 6.0f, 8.0f })
	{
		VALIDATION_ERROR("multiply({ 2, 2, 2, 2 }, { 1, 2, 3, 4 })");
		return 15;
	}


	else if (fx::total(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != 4.0f)
	{
		VALIDATION_ERROR("total({ 1, 1, 1, 1 })");
		return 16;
	}

	else if (fx::total(fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != 10.0f)
	{
		VALIDATION_ERROR("total({ 1, 2, 3, 4 })");
		return 17;
	}


	else if (fx::magnitude(fx::vec4{ 1.0f, 0.0f, 0.0f, 0.0f }) != 1.0f)
	{
		VALIDATION_ERROR("magnitude({ 1, 0, 0, 0 })");
		return 18;
	}

	else if (fx::magnitude(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != 2.0f)
	{
		VALIDATION_ERROR("magnitude({ 1, 1, 1, 1 })");
		return 19;
	}


	else if (fx::normalize(fx::vec4{ 1.0f, 0.0f, 0.0f, 0.0f }) != fx::vec4{ 1.0f, 0.0f, 0.0f, 0.0f })
	{
		VALIDATION_ERROR("normalize({ 1, 0, 0, 0 })");
		return 20;
	}

	else if (fx::normalize(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != fx::vec4{ 0.5f, 0.5f, 0.5f, 0.5f })
	{
		VALIDATION_ERROR("normalize({ 1, 1, 1, 1 })");
		return 21;
	}


	else if (fx::distance(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
		fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != 0.0f)
	{
		VALIDATION_ERROR("distance({ 1, 1, 1, 1 }, { 1, 1, 1, 1 })");
		return 22;
	}

	else if (fx::distance(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
		fx::vec4{ 3.0f, 3.0f, 3.0f, 3.0f }) != 4.0f)
	{
		VALIDATION_ERROR("distance({ 1, 1, 1, 1 }, { 3, 3, 3, 3 })");
		return 23;
	}


	else if (fx::dot(fx::vec4{ 0.0f, 0.0f, 0.0f, 0.0f },
					 fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }) != 0.0f)
	{
		VALIDATION_ERROR("dot({ 0, 0, 0, 0 }, { 1, 1, 1, 1 })");
		return 24;
	}

	else if (fx::dot(fx::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
					 fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != 10.0f)
	{
		VALIDATION_ERROR("dot({ 1, 1, 1, 1 }, { 1, 2, 3, 4 })");
		return 25;
	}


	else if (fx::cross(fx::vec3{ 1.0f, 1.0f, 1.0f },
					   fx::vec3{ 1.0f, 2.0f, 3.0f }) != fx::vec3{ 1.0f, -2.0f, 1.0f })
	{
		VALIDATION_ERROR("cross({ 1, 1, 1 }, { 1, 2, 3 })");
		return 26;
	}

	else if (fx::cross(fx::vec3{ 1.0f, 0.0f, 0.0f },
					   fx::vec3{ 1.0f, 1.0f, 1.0f }) != fx::vec3{ 0.0f, -1.0f, 1.0f })
	{
		VALIDATION_ERROR("cross({ 1, 0, 0 }, { 1, 1, 1 })");
		return 27;
	}

	else if (fx::reflect(fx::vec3{ 1.0f, 2.0f, 3.0f },
						 fx::vec3{ 1.0f, 1.0f, 2.0f }) != fx::vec3{ -17.0f, -16.0f, -33.0f })
	{
		VALIDATION_ERROR("reflect({ 1, 2, 3 }, { -1, -1, 1 })");
		return 28;
	}

#pragma endregion

#define ROW4 std::array<float, 4>
#define ROW3 std::array<float, 3>

#pragma region MATRIX_VALIDATION
	if (fx::identity() != fx::mat4{ ROW4{ 1.0f, 0.0f, 0.0f, 0.0f },
									ROW4{ 0.0f, 1.0f, 0.0f, 0.0f },
									ROW4{ 0.0f, 0.0f, 1.0f, 0.0f },
									ROW4{ 0.0f, 0.0f, 0.0f, 1.0f } })
	{
		VALIDATION_ERROR("identity()");
		return 29;
	}


	else if (fx::null() != fx::mat4{ ROW4{ 0.0f, 0.0f, 0.0f, 0.0f },
									 ROW4{ 0.0f, 0.0f, 0.0f, 0.0f },
									 ROW4{ 0.0f, 0.0f, 0.0f, 0.0f },
									 ROW4{ 0.0f, 0.0f, 0.0f, 0.0f } })
	{
		VALIDATION_ERROR("null()");
		return 30;
	}


	else if (fx::constant(1.0f) != fx::mat4{ ROW4{ 1.0f, 1.0f, 1.0f, 1.0f },
											 ROW4{ 1.0f, 1.0f, 1.0f, 1.0f },
											 ROW4{ 1.0f, 1.0f, 1.0f, 1.0f },
											 ROW4{ 1.0f, 1.0f, 1.0f, 1.0f } })
	{
		VALIDATION_ERROR("constant(1.0f)");
		return 31;
	}


	else if (fx::constant(2.0f) != fx::mat4{ ROW4{ 2.0f, 2.0f, 2.0f, 2.0f },
											 ROW4{ 2.0f, 2.0f, 2.0f, 2.0f },
											 ROW4{ 2.0f, 2.0f, 2.0f, 2.0f },
											 ROW4{ 2.0f, 2.0f, 2.0f, 2.0f } })
	{
		VALIDATION_ERROR("constant(1.0f)");
		return 32;
	}

	const fx::mat3 A{ ROW3{ 1.0f, 2.0f, 3.0f },
					  ROW3{ 5.0f, 8.0f, 6.0f },
					  ROW3{ 2.0f, 1.0f, 4.0f } };

	const fx::mat3 At{ ROW3{ 1.0f, 5.0f, 2.0f },
					   ROW3{ 2.0f, 8.0f, 1.0f },
					   ROW3{ 3.0f, 6.0f, 4.0f } };

	if (fx::transpose(A) != At)
	{
		VALIDATION_ERROR("transpose(A)");
		return 33;
	}

	else if (fx::transpose(At) != A)
	{
		VALIDATION_ERROR("transpose(At)");
		return 34;
	}

	else if (fx::determinant(A) != -23.0f)
	{
		VALIDATION_ERROR("determinant(A)");
		return 35;
	}

	else if (fx::determinant(At) != -23.0f)
	{
		VALIDATION_ERROR("determinant(At)");
		return 36;
	}


	else if (fx::translation(fx::vec3{ 1.0f, 2.0f, 3.0f }) != fx::mat4{ ROW4{ 1.0f, 0.0f, 0.0f, 1.0f },
																		ROW4{ 0.0f, 1.0f, 0.0f, 2.0f },
																		ROW4{ 0.0f, 0.0f, 1.0f, 3.0f },
																		ROW4{ 0.0f, 0.0f, 0.0f, 1.0f } })
	{
		VALIDATION_ERROR("translation({ 1, 2, 3 }");
		return 37;
	}

	else if (fx::scale(A, 2.0f) != fx::mat3{ ROW3{ 2.0f,  4.0f,  6.0f  },
											 ROW3{ 10.0f, 16.0f, 12.0f },
											 ROW3{ 4.0f,  2.0f,  8.0f  } })
	{
		VALIDATION_ERROR("scale(A, 2)");
		return 38;
	}

	const fx::mat4 B{ ROW4{  1.0f,  2.0f,  3.0f,  4.0f },
					  ROW4{ -8.0f, -7.0f, -6.0f, -3.0f },
					  ROW4{ -2.0f,  1.0f, -4.0f, -3.0f },
					  ROW4{  0.0f,  1.0f,  2.0f, -2.0f } };

	const fx::mat4 C{ ROW4{ -1.0f, -3.0f, -7.0f,  4.0f },
					  ROW4{  5.0f,  3.0f,  1.0f,  3.0f },
					  ROW4{  3.0f,  2.0f,  0.0f,  0.0f },
					  ROW4{ -3.0f,  2.0f, -1.0f,  4.0f } };

	if (fx::multiply(B, C) != fx::mat4{ ROW4{   6.0f,  17.0f, -9.0f,  26.0f },
										ROW4{ -36.0f, -15.0f, 52.0f, -65.0f },
										ROW4{   4.0f,  -5.0f, 18.0f, -17.0f },
										ROW4{   17.0f,  3.0f,  3.0f,  -5.0f } })
	{
		VALIDATION_ERROR("multiply(B, C)");
		return 39;
	}

	else if (fx::apply(B, fx::vec4{ 1.0f, 2.0f, 3.0f, 4.0f }) != fx::vec4{ 30.0f, -52.0f, -24.0f, 0.0f })
	{
		VALIDATION_ERROR("apply(B, { 1, 2, 3, 4 })");
		return 40;
	}

	// TODO: test minors, cofactors, adjugate, inverse
	// TODO: test perspective
	// TODO: test lookat

#pragma endregion

	return 0;
}
