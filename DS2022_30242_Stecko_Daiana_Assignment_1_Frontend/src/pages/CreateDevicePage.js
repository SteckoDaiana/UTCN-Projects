import Header from "../components/User/UserHeader";
import CreateDevice from "../components/Device/CreateDevice";
import LoginPage from "./Login";
function CreateDevicePage() {
  return (
    <>
      <Header heading="This is what you have to do to create a device !" />

      <div className=" flex justify-center  font-extrabold text-gray-900"></div>

      <CreateDevice />
    </>
  );
}
export default sessionStorage.getItem("admUID") ? CreateDevicePage : LoginPage;
