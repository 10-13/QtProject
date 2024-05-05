#include "core/includes/Includes.h"
#include "core/data/DValue.h"

namespace qtproject
{
    namespace data
    {
        namespace require
        {
            struct InputRequest {
                std::string Path;
                std::string Request;

                enum class Type {
                    User = 'u',
                    Numeric = 'n',
                    Floating = 'f',
                    Date = 'd',
                    Variants = 'v',
                    VariantsOrUser = 'i',
                };

                Type GetRequestType() {
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
                public:
                std::shared_ptr<DValue> Pattern;

                StructureChecker() = default;

                bool CheckValue(std::shared_ptr<DValue> source);
                void RestorePathes(std::shared_ptr<DValue> source);
                std::vector<InputRequest> GetRequiredInputs(std::shared_ptr<DValue> source);

                static bool CheckValue(std::string&& source, std::string request);
                static void RestorePath(std::shared_ptr<DValue> source, std::vector<std::string> path);
            };
        }
    }
}