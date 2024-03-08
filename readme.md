# C++ Express-Like Framework

## Project Overview

Welcome to the C++ Express-Like Framework project! This is an educational initiative aimed at exploring the development of a web framework in C++ inspired by Express.js. The project is to learn c++

## Features

- **Routing System:** Create routes for handling HTTP requests and defining their corresponding handlers.
- **Middleware Support:** Implement middleware functions to perform tasks before or after the main request handler.
- **Request and Response Objects:** Manipulate HTTP request and response objects to handle incoming requests and send responses.

## Getting Started

### Prerequisites

- C++ Compiler (Supporting C++11 or later)
- CMake (Minimum version: 3.12)
- Git

### Installation

1. Clone the repository:

    ```bash
    https://github.com/sagarkhadka12345/express-cpp.git
    ```


2. Run the example:

    ```bash
    Use Visual Studio and run the project
    ```

## Usage

1. **Define Routes:**
   Open `App.cpp` and define your routes by using the `app.get`, `app.post`, etc. functions.

    ```cpp
    #include "Server.h"

    int main() {
       Server server = Server<std::string>(3000);

        server.Get("/:user_id", server_message);

        app.listen(3000);

        return 0;
    }
    ```



2. **Run the Application:**
   Compile and run your application. Access it through a web browser or tools like curl.

## Contributing

We welcome contributions! Feel free to submit issues, feature requests, or pull requests. Check out the [contribution guidelines](CONTRIBUTING.md) for more details.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- The project is inspired by the simplicity and elegance of Express.js.
- Thanks to the C++ community for valuable resources and discussions.

Happy coding! 🚀
