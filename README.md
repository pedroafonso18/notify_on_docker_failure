# Container Monitor

A C application that monitors Docker containers and sends notifications when they stop running. The application checks a list of specified containers and sends alerts to a Rocket.Chat channel when any container is found to be stopped.

## Features

- Monitors multiple Docker containers simultaneously
- Configurable container list via TOML configuration
- Sends notifications to Rocket.Chat with container name and server IP
- Environment variable support for API authentication
- Automatic retry mechanism with configurable intervals

## Prerequisites

- C compiler (GCC recommended)
- CMake (version 3.10 or higher)
- libcurl
- Docker
- Linux/Unix environment (for Docker commands)

## Dependencies

The project uses the following external libraries:
- libcurl: For making HTTP requests
- tomlc99: For parsing TOML configuration files
- dotenv: For loading environment variables

## Building

1. Clone the repository:
```bash
git clone [repository-url]
cd [repository-name]
```

2. Create a build directory and build the project:
```bash
mkdir build
cd build
cmake ..
make
```

The executable will be created in `build/bin/notifica-rabbit`

## Configuration

### Environment Variables

Create a `.env` file in the project root with the following variables:
```
XAUTH=your_rocket_chat_auth_token
XUSER=your_rocket_chat_user_id
```

### TOML Configuration

Create a `config.toml` file in the project root with the following structure:
```toml
[list]
enabled = true
processes = ["container1", "container2", "container3"]
```

- `enabled`: Set to `true` to enable monitoring
- `processes`: Array of container names to monitor

## Usage

1. Set up your environment variables and configuration files
2. Run the executable:
```bash
./build/bin/notifica-rabbit
```

The program will:
- Check the status of configured containers every 100 seconds
- Send a notification to the specified Rocket.Chat channel when a container is found stopped
- Include the container name and server IP in the notification

## Notification Format

Notifications are sent to the Rocket.Chat channel in the following format:
```
Container [container_name] PARADO @pedro.afonso (IP: [server_ip])
```

## Error Handling

- The program will retry every 5 seconds if it fails to check container status
- Failed API requests are logged to stderr
- Invalid configurations will cause the program to exit with an error message

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request

## License

MIT License

## Author

Pedro Afonso