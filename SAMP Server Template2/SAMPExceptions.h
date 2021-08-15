#ifndef SAMP_EXCEPTIONS_H
#define SAMP_EXCEPTIONS_H


namespace SAMP_SDK {
	namespace Exceptions {
		class VehicleDoesNotExist : public ::Exceptions::Exception {
		public:
			VehicleDoesNotExist() noexcept;
			VehicleDoesNotExist(const char* msg) noexcept;
			~VehicleDoesNotExist() noexcept;
		};
		class InvalidVehicleID : public ::Exceptions::Exception {

		};
		class OutOfBoundsVehicleID : InvalidVehicleID {

		};
		class PlayerDoesNotExist : public ::Exceptions::Exception {

		};
		class InvalidPlayerID : public ::Exceptions::Exception {

		};
		class OutOfBoundsPlayerID : InvalidPlayerID {

		};
	}
}

#endif