/*
 * Blowfish.hpp
 *
 *  Created on: 13 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef BLOWFISH_HPP_
#define BLOWFISH_HPP_

typedef dword t_bf_p[18];
typedef dword t_bf_s[4][256];

class Blowfish
{
public:
    void set_key(const byte* key, int cb_key);
    void encipher(dword& xl, dword& xr) const;
    void encipher(const void* s, void* d, int size) const;
    void decipher(dword& xl, dword& xr) const;
    void decipher(const void* s, void* d, int size) const;
private:
    inline dword S(dword x, int i) const;
    inline dword bf_f(dword x) const;
    inline void ROUND(dword& a, dword b, int n) const;

    t_bf_p m_p;
    t_bf_s m_s;
};

#endif /* BLOWFISH_HPP_ */
