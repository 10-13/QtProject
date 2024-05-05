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