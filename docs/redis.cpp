#include <cpp_redis/cpp_redis>

int main() {
    cpp_redis::client client("localhost", 6379);

    // Чтение данных
    auto reply = client.get("ключ");
    if (reply.is_string()) {
        std::cout << "Значение: " << reply.as_string() << std::endl;
    }

    // Запись данных (put, аналог set)
    client.set("ключ", "значение");

    // Удаление данных
    client.del("ключ");

    return 0;
}

