#include <functional>
#include <random>


std::vector<unsigned int> birthday_attack_1(std::function<unsigned short(unsigned int)> hash_function);

unsigned short hash(unsigned int input) {
    const unsigned int a = 3177205741;
    const unsigned int b = 2371597069;
    return static_cast<unsigned short>(a*input + b);
}

unsigned short constant_hash(unsigned int input){
    return static_cast<unsigned short>(42);
}

unsigned short modulo_hash(unsigned int input) {
    return static_cast<unsigned short>(input % 100);
}

unsigned short double_hash(unsigned int input) {
    return static_cast<unsigned short>(hash(hash(input)));
}

unsigned short xor_hash(unsigned int input) {
    return static_cast<unsigned short>((input >> 16) ^ (input & 0xFFFF));
}

int main() {
    double total_score = 5.0;
    double score = 0.0;

    for(int i = 0; i < 10; ++i) {
        std::vector<unsigned int> result = birthday_attack_1(hash);
        if(result.size() != 2) {
            continue;
        }
        if(hash(result[0]) == hash(result[1]) && result[0] != result[1]) {
            score += 10.0;
            break;
        }
    }

    // Test constant hash function
    for(int i = 0; i < 10; ++i) {
        std::vector<unsigned int> result = birthday_attack_1(constant_hash);
        if(result.size() != 2) {
            continue;
        }
        if(constant_hash(result[0]) == constant_hash(result[1]) && result[0] != result[1]) {
            score += 10.0;
            break;
        }
    }

    // Test modulo hash function
    for(int i = 0; i < 10; ++i) {
        std::vector<unsigned int> result = birthday_attack_1(modulo_hash);
        if(result.size() != 2) {
            continue;
        }
        if(modulo_hash(result[0]) == modulo_hash(result[1]) && result[0] != result[1]) {
            score += 10.0;
            break;
        }
    }

    // Test double hash function
    for(int i = 0; i < 10; ++i) {
        std::vector<unsigned int> result = birthday_attack_1(double_hash);
        if(result.size() != 2) {
            continue;
        }
        if(double_hash(result[0]) == double_hash(result[1]) && result[0] != result[1]) {
            score += 10.0;
            break;
        }
    }

    // Test xor hash function
    for(int i = 0; i < 10; ++i) {
        std::vector<unsigned int> result = birthday_attack_1(xor_hash);
        if(result.size() != 2) {
            continue;
        }
        if(xor_hash(result[0]) == xor_hash(result[1]) && result[0] != result[1]) {
            score += 10.0;
            break;
        }
    }


    RESULT(100*((score/10) / total_score));

    return 0;
}