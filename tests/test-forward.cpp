#include <gtest/gtest.h>
#include <lung/lung.hpp>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

namespace rc {
    template<typename Precision>
    struct Arbitrary<ventilation::Elastance<Precision>> {
        static Gen<ventilation::Elastance<Precision>>
        arbitrary() {
            return gen::construct<ventilation::Elastance<Precision>>(
                    gen::cast<Precision>(gen::inRange(-100, 100))
                    );
        }
    };

    template<typename Precision>
    struct Arbitrary<ventilation::Resistance<Precision>> {
        static Gen<ventilation::Resistance<Precision>>
        arbitrary() {
            return gen::construct<ventilation::Resistance<Precision>>(
                    gen::cast<Precision>(gen::inRange(-100, 100))
                    );
        }
    };

    template<typename Precision>
    struct Arbitrary<ventilation::Flow<Precision>> {
        static Gen<ventilation::Flow<Precision>>
        arbitrary() {
            return gen::construct<ventilation::Flow<Precision>>(
                    gen::cast<Precision>(gen::inRange(-100, 100))
                    );
        }
    };

    template<typename Precision>
    struct Arbitrary<ventilation::Pressure<Precision>> {
        static Gen<ventilation::Pressure<Precision>>
        arbitrary() {
            return gen::construct<ventilation::Pressure<Precision>>(
                    gen::cast<Precision>(gen::inRange(-100, 100))
                    );
        }
    };

    template<typename Precision>
    struct Arbitrary<ventilation::Volume<Precision>> {
        static Gen<ventilation::Volume<Precision>>
        arbitrary() {
            return gen::construct<ventilation::Volume<Precision>>(
                    gen::cast<Precision>(gen::inRange(-100, 100))
                    );
        }
    };

    template<typename Precision>
    struct Arbitrary<lung::Forward<Precision>> {
        static Gen<lung::Forward<Precision>>
        arbitrary() {
            return gen::construct<lung::Forward<Precision>>(
                      gen::arbitrary<ventilation::Resistance<Precision>>()
                    , gen::arbitrary<ventilation::Elastance<Precision>>()
                    );
        }
    };
} // namespace rc

namespace f32 {
    using Flow      = ventilation::Flow<float>;
    using Pressure  = ventilation::Pressure<float>;
    using Volume    = ventilation::Volume<float>;
    using Lung      = lung::Forward<float>;

    RC_GTEST_PROP(Add, Scale, (const Lung& lung, const Volume& volume, const Flow& flow)) {
        {
            Pressure expected   = 2.0f * lung(flow, Volume(0.0f));
            Pressure actual     = lung(2.0f * flow, Volume(0.0f));
            RC_ASSERT(expected == actual);
        }
        {
            Pressure expected   = 2.0f * lung(Flow(0.0f), volume);
            Pressure actual     = lung(Flow(0.0f), 2.0f * volume);
            RC_ASSERT(expected == actual);
        }
    }

    RC_GTEST_PROP(Add, Zero, (const Lung& lung)) {
        RC_ASSERT(Pressure(0.0f) == lung(Flow(0.0f), Volume(0.0f)));
    }
} // namespace f32
namespace f64 {
    using Flow      = ventilation::Flow<double>;
    using Pressure  = ventilation::Pressure<double>;
    using Volume    = ventilation::Volume<double>;
    using Lung      = lung::Forward<double>;

    RC_GTEST_PROP(Add, Scale, (const Lung& lung, const Volume& volume, const Flow& flow)) {
        {
            Pressure expected   = 2.0 * lung(flow, Volume(0.0));
            Pressure actual     = lung(2.0 * flow, Volume(0.0));
            RC_ASSERT(expected == actual);
        }
        {
            Pressure expected   = 2.0 * lung(Flow(0.0), volume);
            Pressure actual     = lung(Flow(0.0), 2.0 * volume);
            RC_ASSERT(expected == actual);
        }
    }

    RC_GTEST_PROP(Add, Zero, (const Lung& lung)) {
        RC_ASSERT(Pressure(0.0) == lung(Flow(0.0), Volume(0.0)));
    }
} // namespace f64
namespace f128 {
    using Flow      = ventilation::Flow<long double>;
    using Pressure  = ventilation::Pressure<long double>;
    using Volume    = ventilation::Volume<long double>;
    using Lung      = lung::Forward<long double>;

    RC_GTEST_PROP(Add, Scale, (const Lung& lung, const Volume& volume, const Flow& flow)) {
        {
            Pressure expected   = 2.0 * lung(flow, Volume(0.0));
            Pressure actual     = lung(2.0 * flow, Volume(0.0));
            RC_ASSERT(expected == actual);
        }
        {
            Pressure expected   = 2.0 * lung(Flow(0.0), volume);
            Pressure actual     = lung(Flow(0.0), 2.0 * volume);
            RC_ASSERT(expected == actual);
        }
    }

    RC_GTEST_PROP(Add, Zero, (const Lung& lung)) {
        RC_ASSERT(Pressure(0.0) == lung(Flow(0.0), Volume(0.0)));
    }
} // namespace f128

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
