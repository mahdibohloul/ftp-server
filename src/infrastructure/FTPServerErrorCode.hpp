//
// Created by mahdi on 24/03/2022.
//

#ifndef FTP_SERVER_FTPSERVERERRORCODE_HPP
#define FTP_SERVER_FTPSERVERERRORCODE_HPP

namespace ftp_error_code {
    const int OK = 200;
    const int INTERNAL_ERROR = 500;
    const int ALREADY_LOGGED_IN = 530;
    const int USERNAME_OK = 331;
    const int INVALID_USERNAME_OR_PASSWORD = 430;
    const int MISSING_ARGUMENT = 501;
    const int TOO_MANY_ARGUMENTS = 501;
    const int BAD_SEQUENCE_OF_COMMANDS = 503;
    const int LOGIN_SUCCESSFUL = 230;
}

#endif //FTP_SERVER_FTPSERVERERRORCODE_HPP
