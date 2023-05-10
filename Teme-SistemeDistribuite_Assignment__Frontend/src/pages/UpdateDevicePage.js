import Header from "../components/User/UserHeader";
import UpdateDevice from "../components/Device/UpdateDevice";
import LoginPage from "./Login";
function UpdateDevicePage() {
  return (
    <>
      <Header heading="This is what you have to do to create an user !" />

      <div className=" flex justify-center  font-extrabold text-gray-900"></div>

      <UpdateDevice />
    </>
  );
}
export default sessionStorage.getItem("admUID") ? UpdateDevicePage : LoginPage;
