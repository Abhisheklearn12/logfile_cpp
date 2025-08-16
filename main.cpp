// Log File

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

// RAII wrapper for a file
class FileWriter {
public:
    FileWriter(const std::string &filename) : ofs(filename, std::ios::app) {
        if (!ofs.is_open()) {
            throw std::runtime_error(fmt::format("Cannot open file '{}'", filename));
        }
    }

    void write(const std::string &message) {
        ofs << message << "\n";
    }

private:
    std::ofstream ofs;
};

// A complex struct
struct User {
    int id;
    std::string name;
    double score;
};

// Formatter specialization for fmt
template <>
struct fmt::formatter<User> {
    constexpr auto parse(fmt::format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const User &u, FormatContext &ctx) {
        return fmt::format_to(
            ctx.out(),
            "User(id={}, name='{}', score={:.2f})",
            u.id, u.name, u.score
        );
    }
};

// Logging helper
void log_info(const std::string &message) {
    auto now = std::chrono::system_clock::now();
    fmt::print("[{}] INFO: {}\n", fmt::localtime(std::chrono::system_clock::to_time_t(now)), message);
}

int main() {
    try {
        // RAII file writer
        FileWriter log_file("app.log");

        // Some users
        std::vector<User> users = {
            {1, "Alice", 95.5},
            {2, "Bob", 87.3},
            {3, "Charlie", 91.2}
        };

        // Print all users to console and log file
        for (const auto &user : users) {
            fmt::print("{}", user);             // Console output
            fmt::print("\n");
            log_file.write(fmt::format("{}", user)); // File output
        }

        // Structured log
        log_info(fmt::format("Processed {} users", users.size()));

        // Complex formatting example
        fmt::print("Top user: {0} with score {1:.2f}\n", users[0].name, users[0].score);

    } catch (const std::exception &e) {
        fmt::print(stderr, "Exception: {}\n", e.what());
        return 1;
    }

    return 0;
}
