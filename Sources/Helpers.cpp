#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include <memory>
#include <string>
#include <stdexcept>

extern std::vector<std::string> approvedCodes;

using namespace CTRPluginFramework;

bool IsOnWhiteList(void)
{
    FriendKey FKey;
    u64 FCode;
  
    if (approvedCodes.size() == 0)
        return true;

    frdInit();
    FRD_GetMyFriendKey(&FKey);
    FRD_PrincipalIdToFriendCode(FKey.principalId, &FCode);

    std::string FriendCode = std::string(12 - std::to_string(FCode).length(), '0') + std::to_string(FCode);
    
    return !(std::find(approvedCodes.begin(), approvedCodes.end(), FriendCode) == approvedCodes.end());
}