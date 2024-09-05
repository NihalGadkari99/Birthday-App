#include <jni.h>
#include <string>
#include <vector>

std::string base64_encode(const std::string &in) {
    std::string out;
    int val = 0, valb = -6;
    static const char *b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(b64[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(b64[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

std::string base64_decode(const std::string &in) {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_birthday_MainActivity_convertToBase64(JNIEnv *env, __attribute__((unused)) jobject thiz, jstring input) {
    const char *nativeString = env->GetStringUTFChars(input, nullptr);
    std::string encoded = base64_encode(nativeString);
    env->ReleaseStringUTFChars(input, nativeString);
    return env->NewStringUTF(encoded.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_birthday_MainActivity_convertFromBase64(JNIEnv *env,
                                                         __attribute__((unused)) jobject thiz, jstring input) {
    const char *nativeString = env->GetStringUTFChars(input, nullptr);
    std::string decoded = base64_decode(nativeString);
    env->ReleaseStringUTFChars(input, nativeString);
    return env->NewStringUTF(decoded.c_str());
}
