#ifndef FLUX_MATRIX_H
#define FLUX_MATRIX_H

#include "base.h"
#include "vector.h"

// matrix.h
// (c) 2025 Connor J. Link. All Rights Reserved.

namespace fx
{
	template<std::size_t M = 4, typename T = platform_type>
	constexpr mat<M, M, T> identity()
	{
		mat<M, M, T> out{};

		for (auto ij = 0; ij < M; ij++)
		{
			out[ij][ij] = T{ 1 };
		}

		return out;
	}

	template<std::size_t M = 4, typename T = platform_type>
	constexpr mat<M, M, T> null()
	{
		return {};
	}

	template<std::size_t M = 4, std::size_t N = 4, typename T = platform_type>
	constexpr mat<M, N, T> constant(T value)
	{
		mat<M, N, T> out{};

		for (auto i = 0; i < M; i++)
		{
			for (auto j = 0; j < N; j++)
			{
				out[i][j] = value;
			}
		}

		return out;
	}

	template<std::size_t M = 4, std::size_t N = 4, typename T = platform_type>
	constexpr mat<N, M, T> transpose(const mat<M, N, T>& matrix)
	{
		mat<N, M, T> out{};

		for (auto i = 0; i < N; i++)
		{
			for (auto j = 0; j < M; j++)
			{
				out[i][j] = matrix[j][i];
			}
		}

		return out;
	}

	template<std::size_t M, typename T>
	constexpr T determinant(const mat<M, M, T>& matrix)
	{
		static_assert(false, "Determinant argument is of an unsupported size.");
	}

	// NOTE: overloading because partial function template specialization not allowed
	template<typename T = platform_type>
	constexpr T determinant(const mat<2, 2, T>& matrix)
	{
		const auto forward = matrix[0][0] * matrix[1][1];
		const auto backward = matrix[0][1] * matrix[1][0];

		const auto difference = forward - backward;

		return difference;
	}

	// NOTE: overloading because partial function template specialization not allowed
	template<typename T = platform_type>
	constexpr T determinant(const mat<3, 3, T>& matrix)
	{
		const auto forward = _forward_diagonals(matrix);
		const auto backward = _backward_diagonals(matrix);

		const auto difference = total(forward) - total(backward);

		return difference;
	}

	// NOTE: overloading because partial function template specialization not allowed
	template<typename T = platform_type>
	constexpr T determinant(const mat<4, 4, T>& matrix)
	{
		auto det = T{ 0 };

		for (std::size_t i = 0; i < 4; ++i)
		{
			mat<3, 3, T> minors{};

			for (std::size_t j = 1; j < 4; ++j)
			{
				std::size_t l = 0;

				for (std::size_t k = 0; k < 4; ++k)
				{
					if (k == i) continue;

					minors[j - 1][l] = matrix[j][k];
					++l;
				}
			}

			// equivalent to `((i % 2 == 0) ? 1 : -1)`
			const auto sign = 1 - ((i & 1) << 1);
			const auto cofactor = sign * matrix[0][i] * determinant(minors);

			det += cofactor;
		}

		return det;
	}

	template<std::size_t M = 4, typename T = platform_type>
	constexpr mat<M, M, T> minors(const mat<M, M, T>& matrix)
	{
		mat<M, M, T> out{};

		for (auto i = 0; i < M; i++)
		{
			for (auto j = 0; j < M; j++)
			{
				auto temp = matrix;

				for (auto k = 0; k < M; k++)
				{
					temp[i][k] = 1;
					temp[k][j] = 1;
				}

				out[i][j] = determinant(temp);
			}
		}

		return out;
	}

	template<std::size_t M = 4, typename T = platform_type>
	constexpr mat<M, M, T> cofactors(const mat<M, M, T>& matrix)
	{
		mat<M, M, T> out = minors(matrix);

		for (auto i = 0; i < M; i++)
		{
			for (auto j = 0; j < M; j++)
			{
				if ((i + j) & 1)
				{
					out[i][j] *= -1;
				}
			}
		}

		return out;
	}

	template<std::size_t M = 4, typename T = platform_type>
	constexpr mat<M, M, T> adjugate(const mat<M, M, T>& matrix)
	{
		return transpose(cofactors(matrix));
	}

	template<std::size_t M = 4, typename T = platform_type>
	constexpr mat<M, M, T> inverse(const mat<M, M, T>& matrix)
	{
		const auto scalar = 1 / determinant(matrix);
		const auto base = adjugate(matrix);

		return scale(base, scalar);
	}

	template<std::size_t M = 4, typename T = platform_type>
	constexpr mat<M, M, T> translation(const vec<M - 1, T>& vector)
	{
		auto out = identity<M, T>();

		for (auto i = 0; i < M - 1; i++)
		{
			out[i][M - 1] = vector[i];
		}

		return out;
	}

	template<typename T = platform_type>
	constexpr mat<4, 4, T> perspective(T fov, T width, T height, T front, T back)
	{
		// NOTE: fov is measured in radians
		// NOTE: front -> near, back -> far

		const auto reciprocal_aspect = height / width;
		const auto reciprocal_tan = 1 / std::tan(fov / 2);
		const auto difference = back - front;

		mat<4, 4, T> out{};

		out[0][0] = reciprocal_tan * reciprocal_aspect;
		out[1][1] = reciprocal_tan;
		out[2][2] = -(back + front) / difference;
		out[2][3] = -(2 * back * front) / difference;
		out[3][2] = -1;

		return out;
	}

	template<std::size_t M = 4, std::size_t N = 4, typename T = platform_type>
	constexpr mat<M, N, T> scale(const mat<M, N, T>& matrix, T scalar)
	{
		mat<M, N, T> out{};

		for (auto i = 0; i < M; i++)
		{
			for (auto j = 0; j < N; j++)
			{
				out[i][j] = matrix[i][j] * scalar;
			}
		}

		return out;
	}

	template<std::size_t M = 4, std::size_t R = 4, std::size_t N = 4, typename T = platform_type>
	constexpr mat<M, N, T> multiply(const mat<M, R, T>& matrix1, const mat<R, N, T>& matrix2)
	{
		mat<M, N, T> out{};

		for (auto i = 0; i < M; i++)
		{
			for (auto j = 0; j < N; j++)
			{
				for (auto k = 0; k < M; k++)
				{
					out[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}

		return out;
	}

	template<std::size_t M = 4, std::size_t N = 4, typename T = platform_type>
	constexpr vec<N, T> apply(const mat<M, N, T>& matrix, const vec<N, T>& vector)
	{
		vec<N, T> out{};

		for (auto i = 0; i < M; i++)
		{
			for (auto j = 0; j < N; j++)
			{
				out[i] += matrix[i][j] * vector[j];
			}
		}

		return out;
	}

	template<std::size_t M = 4, typename T = platform_type>
		requires (M == 4)
	constexpr mat<M, M, T> lookat(const vec<M - 1, T>& at, const vec<M - 1, T>& eye, const vec<M - 1, T>& up)
	{
		const auto zaxis = normalize(subtract(at, eye));
		const auto xaxis = normalize(cross(up, zaxis));
		const auto yaxis = normalize(cross(zaxis, xaxis));

		return mat<M, M, T>
		{
			std::array<T, M>{ xaxis[0],         yaxis[0],         zaxis[0],         0 },
			std::array<T, M>{ xaxis[1],         yaxis[1],         zaxis[1],         0 },
			std::array<T, M>{ xaxis[2],         yaxis[2],         zaxis[2],         0 },
			std::array<T, M>{ -dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1 },
		};
	}
}

#endif
