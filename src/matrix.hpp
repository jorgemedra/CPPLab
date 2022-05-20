
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <limits>

namespace jomt::data
{

    template <class T, size_t M, size_t N>
    class matrix
    {
        using type = T;
        using type_ref = T&;

        std::array<type, M * N> m_mtrx;

    public:
        matrix<type, M, N>()
        {
            static_assert(std::is_arithmetic<T>::value, "Data Type must be an arithmetic type.");            
            m_mtrx.fill(std::numeric_limits<type>::min());
        }

        matrix<type, M, N>(type value)
        {
            static_assert(std::is_arithmetic<T>::value, "Data Type must be an arithmetic type.");
            m_mtrx.fill(value);
        }

        matrix<type, M, N>(std::vector<std::vector<T>> list)
        {
            static_assert( std::is_arithmetic<T>::value, "Data Type must be an arithmetic type.");

            if (N <= 0 || M <= 0) return;
            else if (list.size() != M || list[0].size() != N) return;
            
            size_t idx{0};
            for(auto itr = list.begin(); itr != list.end(); itr++)
            {
                for (auto itc = itr->begin(); itc != itr->end(); itc++)
                    m_mtrx[idx++] = *itc;
            }
        }

        std::string info(){
            std::stringstream out;

            out << "\n----- BEGIN MATRIX -----";

            size_t c_row{1};
            size_t pos{0};
            for (auto it = m_mtrx.begin(); it != m_mtrx.end(); it++)
            {
                size_t row = pos++ / M;
                char sp = row != c_row ? '\n' : '\t';
                c_row = row;
                out << sp;
                if (std::is_floating_point<T>::value)
                    out << std::fixed << std::setw(11) << std::setprecision(6) << std::setfill(' ') << *it;
                else
                   out << *it;
            }

            // for(size_t i=0; i< M; i++)
            // {
            //     out << '\n';
            //     for (size_t j = 0; j < N; j++)
            //     {
            //         out << '\t';
            //         if (std::is_floating_point<T>::value)
            //             out << std::fixed << std::setw(11) << std::setprecision(6) << std::setfill(' ') << operator()(i, j);
            //         else
            //             out << operator()(i, j);
            //     }
            // }
            out << "\n----- END MATRIX -----\n";
            return out.str();
        }

        size_t cols() const { return N; }
        size_t rows() const { return M; }

        type_ref operator()(size_t m, size_t n)
        {
            return m_mtrx[m * N + n];
        }

        matrix& operator+=(const matrix& om){
            if(m_mtrx.size() != om.m_mtrx.size()) 
                return *this;

            for(size_t i = 0; i< m_mtrx.size(); i++)
                m_mtrx[i] += om.m_mtrx[i];

            return *this;
        }

        friend matrix operator+(matrix a, const matrix &b)
        {
            a += b; // reuse compound assignment
            return a; // return the result by value (uses move constructor)
        }
        
        matrix &operator-=(const matrix &om)
        {
            if (m_mtrx.size() != om.m_mtrx.size())
                return *this;

            for (size_t i = 0; i < m_mtrx.size(); i++)
                m_mtrx[i] -= om.m_mtrx[i];

            return *this;
        }

        friend matrix operator-(matrix a, const matrix &b)
        {
            a -= b;   // reuse compound assignment
            return a; // return the result by value (uses move constructor)
        }

        matrix& operator*=(const type &scalar)
        {
             for (size_t i = 0; i < m_mtrx.size(); i++)
                 m_mtrx[i] *= scalar;

            return *this;
        }

        friend matrix operator*(matrix a, const type &scalar)
        {
            a *= scalar; // reuse compound assignment
            return a; // return the result by value (uses move constructor)
        }
    };

    template <class T, size_t M, size_t N, size_t P>
    matrix<T, M, P> operator*(matrix<T, M, N> &lm, matrix<T, N, P> &rm)
    {
        matrix<T, M, P> mtrx(0);
        for(size_t i = 0; i< M; i++)
            for (size_t j = 0; j < P; j++)
                for (size_t k = 0; k < N; k++)
                {
                    // std::cout << "\n\tSetting mtrx(" << i << ", " << j << ") = " << mtrx(i, j);
                    // std::cout << "\n\t\t lm(" << i << ", " << k << ") = " << lm(i, k);
                    // std::cout << "\n\t\t rm(" << k << ", " << j << ") = " << rm(k, j);
                    mtrx(i, j) += lm(i, k) * rm(k, j);
                    // std::cout << "\n\tNew mtrx(" << i << ", " << j << ") = " << mtrx(i, j) << "";
                }
        return mtrx;
    }

}


#endif