#ifndef LUNG_HPP__
#define LUNG_HPP__

#include <ventilation/ventilation.hpp>

namespace lung {
    template <typename Precision>
    class Forward {
        public:
            Forward(
                      const ventilation::Resistance<Precision>& resistance
                    , const ventilation::Elastance<Precision>&  elastance
                    )
                : resistance_(resistance)
                , elastance_(elastance)
            {}

            Forward(
                      const ventilation::Resistance<Precision>& resistance
                    , const ventilation::Compliance<Precision>& compliance
                    )
                : resistance_(resistance)
            {
                Precision c = static_cast<Precision>(compliance);
                elastance_  = ventilation::Elastance(1.0 / c);
            }

            ventilation::Pressure<Precision>
            operator()(
                      const ventilation::Flow<Precision>&   flow
                    , const ventilation::Volume<Precision>& volume
                    ) const {
                return flow * resistance_ + volume * elastance_;
            }

            const ventilation::Resistance<Precision>&
            resistance() const { return resistance_; }

            const ventilation::Elastance<Precision>&
            elastance() const { return elastance_; }
        private:
            ventilation::Resistance<Precision>   resistance_;
            ventilation::Elastance<Precision>    elastance_;
    };
} // namespace lung

#endif // LUNG_HPP__
