## SIMD

*Instruccion Unica Datos Multiples*

Técnica mediante la cual una CPU realiza una sola operación utilizando múltiples elementos de datos de forma concurrente. 

Ejemples: Si tienes que sumar 2 a los números {3, 5, 7, 9} :

- Sin SIMD: 3+2=5, luego 5+2=7, luego 7+2=9, luego 9+2=11 → 4 pasos.
- Con SIMD: {3+2, 5+2, 7+2, 9+2} = {5,7,9,11} → 1 paso.
### Ejemplo

```cpp
#include <chrono>
#include <immintrin.h>
#include <iostream>
#include <vector>

using namespace std;

extern "C" void CalcZ_Aavx(float *z, const float *x, const float *y, size_t n);

void CalcZ_Cpp(float *z, const float *x, const float *y, size_t n) {
  for (size_t i = 0; i < n; ++i)
    z[i] = x[i] + y[i];
}

void CalcZ_Iavx(float *z, const float *x, const float *y, size_t n) {
  size_t i = 0;
  const size_t num_simd_elements = 8;
  for (; n - i >= num_simd_elements; i += num_simd_elements) {
    __m256 x_vals = _mm256_loadu_ps(&x[i]);
    __m256 y_vals = _mm256_loadu_ps(&y[i]);
    __m256 z_vals = _mm256_add_ps(x_vals, y_vals);
    _mm256_storeu_ps(&z[i], z_vals);
  }
  for (; i < n; ++i)
    z[i] = x[i] + y[i];
}

int main() {
  const size_t n = 100000000;
  vector<float> x(n, 1.5f);
  vector<float> y(n, 2.3f);
  vector<float> z1(n), z2(n), z3(n);

  auto start = chrono::high_resolution_clock::now();
  CalcZ_Cpp(z1.data(), x.data(), y.data(), n);
  auto end = chrono::high_resolution_clock::now();
  auto duration_cpp = chrono::duration_cast<chrono::microseconds>(end - start);

  start = chrono::high_resolution_clock::now();
  CalcZ_Iavx(z2.data(), x.data(), y.data(), n);
  end = chrono::high_resolution_clock::now();
  auto duration_avx = chrono::duration_cast<chrono::microseconds>(end - start);

  start = chrono::high_resolution_clock::now();
  CalcZ_Aavx(z3.data(), x.data(), y.data(), n);
  end = chrono::high_resolution_clock::now();
  auto duration_asm = chrono::duration_cast<chrono::microseconds>(end - start);

  cout << "Resultados (último elemento): "
       << "Cpp=" << z1[n - 1] << ", Iavx=" << z2[n - 1]
       << ", Aavx=" << z3[n - 1] << endl;
  cout << "Tamaño: " << n << endl;
  cout << "CalcZ_Cpp  : " << duration_cpp.count() << " microsegundos" << endl;
  cout << "CalcZ_Iavx : " << duration_avx.count() << " microsegundos" << endl;
  cout << "CalcZ_Aavx : " << duration_asm.count() << " microsegundos" << endl;

  return 0;
}

```

- `<immintrin.h>`:  Para Trabajar com AVX (Advanced Vector Extensions); Conjunto adicional de instrucciones para los procesadores Intel
- `__m256` : Tipo de dato de 256 bits (32 bytes). Los floats tienen 4 bytes, por lo que almacena 8 bytes
-  `_mm256_loadu_ps`: función que le dice al procesador: "ve a esta direccion, y carga 8 números `float` seguidos de una sola vez".
- `_mm256_add_ps`: Realiza la suma 
-  `_mm256_storeu_ps`: Los almacena en una direccion de memoria

```asm

global CalcZ_Aavx
section .text

NSE equ 8

1                  ; if (n - i) < 8, go to scalar loop

    ; Cargar 8 floats de x e y
    vmovups ymm0, [rsi + rax*4] ; ymm0 = x[i..i+7]
    vmovups ymm1, [rdx + rax*4] ; ymm1 = y[i..i+7]
    vaddps  ymm2, ymm0, ymm1    ; suma
    vmovups [rdi + rax*4], ymm2 ; guardar en z

    add rax, NSE
    jmp .loop1

.loop2:
    cmp rax, rcx
    jae .done

    ; Elemento residual escalar
    vmovss xmm0, [rsi + rax*4]
    vmovss xmm1, [rdx + rax*4]
    vaddss xmm2, xmm0, xmm1
    vmovss [rdi + rax*4], xmm2

    inc rax
    jmp .loop2

.done:
    vzeroupper
    ret

```

- *Intel(R) Core(TM) i5-4200U CPU @ 1.60GHz*

```bash
./programa
Cpp=3.8, Iavx=3.8, Aavx=3.8
Tamaño: 100000000
CalcZ_Cpp  : 378725 microsegundos
CalcZ_Iavx : 160471 microsegundos
CalcZ_Aavx : 104367 microsegundos
```


## Historia 
- 1997: Conjunto de instrucciones SIMD x86 (MMX) | **Intel**
	- Aritmetica de enteros
- 1998: AMD lanza su conjunto de instrucciones (3DNow)
	- Operaciones vectoriales
	- Registros en la FPU
- 1999: Intel lanza estension SIMD de streaming (SSE)
	- registros de 128 bits
	- aritmetica de punto flotante (32 bits)
- 2000: (SSE2) 32 -> 64
	- SSE3/2004
	- SSSE/2006
	- SSE4.1/2008
	- SSE4.2/2008
- 2011: Intel Introdujo procesadores que soportaban un nueva tecnologia (AVX) Registros de 256 bits
- 2013: AVX2
- 2017: AVX-512

## Tipo de datos SIMD

Coleccion contigua de bytes que el proecesador utiliza para realizar una operacion de calculo aritmetico o de manipulacion de datos
- Contenedor generico que almacena multiples instancias de un tipo de datos fundamentel
- Los tipos de datos se enumeran de derecha a izquierda, siendo 0 el menos significativo, y n-1 el mas
- Se almacen en memoria usando la ordenacion little-endian  (almacena en celdas de memoria de 8 bits (1byte),  primero el byte menos significativo)
- Para realizar calculos simultaneos, un operador de 256 bits de ancho puede contener 32 enteros de 8 bits

| Tipo numérico                        | xmmword | ymmword | zmmword |
|--------------------------------------|---------|---------|---------|
| Entero de 8 bits                     | 16      | 32      | 64      |
| Entero de 16 bits                    | 8       | 16      | 32      |
| Entero de 32 bits                    | 4       | 8       | 16      |
| Entero de 64 bits                    | 2       | 4       | 8       |
| Punto flotante de precisión simple   | 4       | 8       | 16      |
| Punto flotante de precisión doble    | 2       | 4       | 8       |
- SIMD(AVX) Implementa aritmetica saturada como sin saturacion

- 








