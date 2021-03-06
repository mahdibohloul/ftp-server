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
    const int NOT_LOGGED_IN = 332;
    const int PWD_SUCCESSFUL = 257;
    const int MKD_SUCCESSFUL = 257;
    const int DELETE_SUCCESSFUL = 250;
    const int SEND_DATA_SUCCESSFUL = 226;
    const int CD_SUCCESSFUL = 250;
    const int ACCESS_DENIED = 550;
    const int RENAME_SUCCESSFUL = 250;
    const int CANNOT_OPEN_DATA_CONNECTION = 425;
    const int QUIT_SUCCESSFUL = 221;
}

#endif //FTP_SERVER_FTPSERVERERRORCODE_HPP
