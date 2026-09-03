# fft-frequency-analysis
Frequency domaon analysis using the Cooley-Tukey FFT algorithm in C++
# FFT Frequency Analysis in C++

A standard-library-only C++ implementation of the **Fast Fourier Transform (FFT)** using the recursive **Cooley-Tukey algorithm**.

The program generates a synthetic signal containing 50 Hz and 120 Hz sine waves, transforms it into the frequency domain, and prints the strongest frequency components as a terminal bar chart.

## What the project demonstrates

- Time-domain to frequency-domain conversion
- Recursive Cooley-Tukey FFT
- Complex numbers and twiddle factors
- Frequency-bin calculation
- Nyquist frequency
- FFT frequency resolution
- Basic terminal spectrum visualization

## Test signal

The program uses:

```text
sin(2π × 50t) + 0.5 × sin(2π × 120t)
```

The expected result is therefore two dominant frequency components:

- **50 Hz** with amplitude 1.0
- **120 Hz** with amplitude 0.5

The 50 Hz component should have roughly twice the magnitude of the 120 Hz component.

## Example output

```text
FFT Analysis - Jasveer Singh
Signal: sin(50 Hz) + 0.5*sin(120 Hz)
Sample rate: 1000 Hz
Samples: 1024
Frequency resolution: 0.976562 Hz/bin

Freq (Hz)    Magnitude    Spectrum
--------------------------------------------
49.8         478.44       ###################################
50.8         120.28       ########
120.1        248.98       ##################
--------------------------------------------

Expected peaks: approximately 50 Hz and 120 Hz.
The 50 Hz component has twice the input amplitude of the 120 Hz component.
```

### Why is the peak near 49.8 Hz instead of exactly 50 Hz?

The FFT frequency spacing is:

```text
frequency resolution = sampleRate / N
                     = 1000 / 1024
                     ≈ 0.9766 Hz
```

Therefore, the FFT bins occur at approximately 0, 0.9766, 1.9531, ..., 49.8047, 50.7813 Hz, etc.

Since 50 Hz does not fall exactly on a bin, its energy is distributed across neighbouring bins. This is why the output can show peaks around 49.8 Hz and 50.8 Hz rather than one bin exactly at 50 Hz.

## FFT theory

The Fast Fourier Transform converts a discrete signal from the time domain into its frequency-domain representation.

A naive Discrete Fourier Transform (DFT) requires:

```text
O(N²)
```

operations.

The Cooley-Tukey FFT reduces this to:

```text
O(N log N)
```

by recursively splitting the input into even- and odd-indexed samples and combining their transforms using complex twiddle factors.

## Important concepts

### Frequency bins

For FFT bin `k`:

```text
frequency(k) = k × sampleRate / N
```

### Nyquist frequency

For a sampling rate of `1000 Hz`, the Nyquist frequency is:

```text
1000 / 2 = 500 Hz
```

Frequencies above the Nyquist limit cannot be uniquely represented without aliasing.

### Power-of-two input

This implementation uses the radix-2 Cooley-Tukey algorithm, so the number of samples must be a power of two.

The example uses:

```text
N = 1024
```

which is a power of two.

## Build and run

### Using g++

```bash
g++ -std=c++17 -O2 fft_analysis.cpp -o fft_analysis
```

Run on Linux/macOS:

```bash
./fft_analysis
```

Run on Windows:

```bash
fft_analysis.exe
```

### Using Visual Studio Developer Command Prompt

```bash
cl /std:c++17 fft_analysis.cpp
fft_analysis.exe
```

## Project structure

```text
fft-frequency-analysis/
├── fft_analysis.cpp
├── README.md
└── .gitignore
```

## Dependencies

No external libraries are required.

The program uses only the C++ standard library.

## Author

**Jasveer Singh**

A C++ implementation of frequency-domain signal analysis using the Cooley-Tukey Fast Fourier Transform.
