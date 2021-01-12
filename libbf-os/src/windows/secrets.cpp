#include <codecvt>

#include <libbf/os/dirs.hpp>
#include <libbf/os/exceptions.hpp>
#include <libbf/os/secret_storage.hpp>
#include <libbf/os/settings.hpp>

#include <nlohmann/json.hpp>

#include <windows.h>
//
#include <wincred.h>
//
#include <tchar.h>

void libbf::os::store(libbf::login_cookie l) {
    std::string pw = nlohmann::json(l).dump();

    int len = MultiByteToWideChar(CP_UTF8, 0, l.get_email().c_str(), -1, nullptr, 0);
    std::wstring email(L"\0", len);
    MultiByteToWideChar(CP_UTF8, 0, l.get_email().c_str(), -1, email.data(), len);

    CREDENTIALW cred = {0};
    cred.Type = CRED_TYPE_GENERIC;
    cred.TargetName = L"BIGFINISH/cookie";
    cred.CredentialBlobSize = 1 + pw.size();
    cred.CredentialBlob = (LPBYTE) pw.c_str();
    cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
    cred.UserName = (LPWSTR) email.c_str();

    if (!::CredWriteW(&cred, 0))
        throw libbf::os::secret_write_failed_exception();
}

libbf::login_cookie libbf::os::retrieve() {
    PCREDENTIAL pcred;
    if (!::CredRead("BIGFINISH/cookie", CRED_TYPE_GENERIC, 0, &pcred))
        throw libbf::os::secret_not_found_exception();
    return nlohmann::json::parse(std::string((char*) pcred->CredentialBlob));
}

void libbf::os::revoke() {
    ::CredDelete("BIGFINISH/cookie", CRED_TYPE_GENERIC, 0);
}