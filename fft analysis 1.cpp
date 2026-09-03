#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <iomanip>

// complex<double> shorthand, saw this trick online
typedef std::complex<double> cd;

const double PI = acos(-1.0);

// FFT implementation - Cooley-Tukey algorithm
// basically splits the array in half recursively then combines
// n has to be power of 2 or it breaks
void fft(std::vector<cd>& a) {
    int n = a.size();
    if (n == 1) return;

    // split into even and odd indices
    std::vector<cd> even(n/2), odd(n/2);
    for (int i = 0; i < n/2; i++) {
        even[i] = a[i*2];
        odd[i] = a[i*2 + 1];
    }

    fft(even);
    fft(odd);

    // combine step - twiddle factor rotates in complex space
    for (int k = 0; k < n/2; k++) {
        double ang = -2 * PI * k / n;
        cd w = cd(cos(ang), sin(ang));
        a[k] = even[k] + w * odd[k];
        a[k + n/2] = even[k] - w * odd[k];
    }
}

// builds a test signal we can verify against
// mixing 50hz and 120hz so we know exactly what the output should look like
std::vector<cd> makeSignal(int N, double sr) {
    std::vector<cd> sig(N);
    for (int i = 0; i < N; i++) {
        double t = (double)i / sr;
        double val = sin(2.0 * PI * 50.0 * t) + 0.5 * sin(2.0 * PI * 120.0 * t);
        sig[i] = cd(val, 0);
    }
    return sig;
}

void showSpectrum(const std::vector<cd>& out, double sr, int N) {
    int half = N / 2;

    // find max magnitude first so we can scale the bars
    double maxVal = 0;
    for (int i = 1; i < half; i++) {
        if (std::abs(out[i]) > maxVal)
            maxVal = std::abs(out[i]);
    }

    std::cout << "\nFreq (Hz)    Magnitude    Spectrum\n";
    std::cout << "--------------------------------------------\n";

    for (int i = 1; i < half; i++) {
        double freq = (double)i * sr / N;
        double mag = std::abs(out[i]);

        // only bother printing if its above noise floor
        if (mag < 10.0) continue;

        int bars = (int)(mag / maxVal * 35);
        std::string bar(bars, '#');

        std::cout << std::left << std::setw(13) << std::fixed
                  << std::setprecision(1) << freq
                  << std::setw(13) << std::setprecision(2) << mag
                  << bar << "\n";
    }
    std::cout << "--------------------------------------------\n";
}

int main() {
    // 1024 samples at 1000hz gives us good resolution
    // anything above 500hz wont show up (nyquist)
    int N = 1024;
    double sampleRate = 1000.0;

    std::cout << "FFT Analysis - Jasveer Singh\n";
    std::cout << "Signal: sin(50hz) + 0.5*sin(120hz)\n\n";

    std::vector<cd> signal = makeSignal(N, sampleRate);

    fft(signal);

    showSpectrum(signal, sampleRate, N);

    std::cout << "\nshould see peaks around 50hz and 120hz\n";
    std::cout << "50hz bar should be roughly twice the size of 120hz\n";

    return 0;
}
