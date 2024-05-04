#include "core/includes/Includes.h"
#include "core/data/DValue.h"

namespace qtproject {
    namespace checker {
        class Rule final {
            using DV = std::shared_ptr<qtproject::data::DValue>;
        public:
            // Returns value greater than zero
            using CheckerFunction = double (*)(DV, DV);

            // Used to generate user friendly output for outfit result
            std::string Name;
            std::string Description;

            enum class Type {
                Critical,
                Base,
                Bonus,
            };

            Rule() = delete;

            Rule(Type ruletype, CheckerFunction func, double max = 1.) : RuleType_(ruletype), Max_(max), Function_(func) { }

            Type GetType() {
                return RuleType_;
            }

            double Apply(DV a, DV b) {
                return Function_(a,b);
            }

            double Max() {
                return Max_;
            }

        private:
            Type RuleType_;
            double Max_;
            CheckerFunction Function_;
        };
    }
}