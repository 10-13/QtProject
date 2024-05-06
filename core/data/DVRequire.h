#include "core/includes/Includes.h"
#include "core/data/DValue.h"

namespace qtproject
{
    namespace data
    {
        namespace require
        {
            struct InputRequest {
                std::vector<std::string> Path;
                std::string Request;
                size_t Index;

                enum class Type {
                    User = 'u',
                    Numeric = 'n',
                    Floating = 'f',
                    Date = 'd',
                    Variants = 'v',
                    VariantsOrUser = 'i',
                };

                Type GetRequestType() const {
                    if(Request.size() < 2)
                        return Type::User;
                    if(Request[0] != '!')
                        return Type::User;
                    switch (Request[1])
                    {
                    case (char)Type::Numeric:
                        return Type::Numeric;
                    case (char)Type::Date:
                        return Type::Date;
                    case (char)Type::Floating:
                        return Type::Floating;
                    case (char)Type::Variants:
                        return Type::Variants;
                    case (char)Type::VariantsOrUser:
                        return Type::VariantsOrUser;
                    default:
                        return Type::User;
                    }
                }
            };

            class StructureChecker {
                private:
                static bool CheckFlag(uint16_t flags, uint16_t target) {
                    return (flags & target) == target;
                }

                static bool CheckBranch(std::shared_ptr<DValue> pattern, std::shared_ptr<DValue> out, uint16_t flags) {
                    for(size_t i = 0; i < pattern->Size(); i++)
                        if((CheckFlag(flags, Flags::TreatPatternValuesAsPath) || !pattern->IsValue()) && out->At(pattern->Content(i)) == std::shared_ptr<DValue>{})
                            return false;
                    return true;
                }

                static bool DeepCheckBranch(std::shared_ptr<DValue> pattern, std::shared_ptr<DValue> out, uint16_t flags) {
                    if(!CheckBranch(pattern, out, flags))
                        return false;
                    
                    for(size_t i = 0; i < pattern->Size(); i++)
                    {
                        if(!pattern->IsValue() && !DeepCheckBranch(pattern->At(i), out->At(pattern->Content(i)), flags))
                            return false;
                    }
                    return true;
                }

                void DeepRestorePathes(std::shared_ptr<DValue> pattern, std::shared_ptr<DValue> out, uint16_t flags) {
                    if (pattern->IsValue() && !CheckFlag(flags, Flags::TreatPatternValuesAsPath)) {
                        return;
                    }

                    for (size_t i = 0; i < pattern->Size(); i++) {
                        std::shared_ptr<DValue> out_child;
                        if (out->At(pattern->Content(i)) == std::shared_ptr<DValue>{}) {
                            out_child = out->Add(std::forward<std::string>(pattern->Content(i)));
                        } else {
                            out_child = out->At(pattern->Content(i));
                        }

                        DeepRestorePathes(pattern->At(i), out_child, flags);
                    }
                }

                void DeepRestorePath(std::shared_ptr<DValue> out, std::vector<std::string>::iterator it, std::vector<std::string>::iterator end) {
                    std::shared_ptr<DValue> out_child;
                    if (out->At(*it) == std::shared_ptr<DValue>{}) {
                        out_child = out->Add(std::forward<std::string>(*it));
                    } else {
                        out_child = out->At(std::forward<std::string>(*it));
                    }
                    if (next(it) != end) {
                        DeepRestorePath(out_child, next(it), end);
                    }
                }
                using Reciver = void(*)(const InputRequest& request);

                public:
                enum Flags {
                    Default                     = 0,
                    TreatPatternValuesAsPath    = 0b0001,
                    IgnoreContentRequests       = 0b0010,
                    UpdateOldValues             = 0b0100,
                };

                std::shared_ptr<DValue> Pattern;
                uint16_t Flags;

                StructureChecker() = default;

                bool CheckValue(std::shared_ptr<DValue> source, uint16_t flags = 0) {
                    if(flags == 0)
                        flags = Flags;
                    return DeepCheckBranch(Pattern, source, flags);
                }

                void RestorePathes(std::shared_ptr<DValue> source, uint16_t flags = 0) {
                    DeepRestorePathes(Pattern, source, flags);
                }

                void GetRequiredInputs(std::shared_ptr<DValue> source, Reciver reciver_function , uint16_t flags = 0)ж

                static bool CheckValue(std::string&& source, std::string request);

                static void RestorePath(std::shared_ptr<DValue> source, std::vector<std::string> path) {
                    DeepRestorePath(source, path.begin(), path.end());
                }
            };
        }
    }
}