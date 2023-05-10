import Header from "../components/User/UserHeader";
import CreateClient from "../components/Client/CreateClient";
import LoginPage from "./Login";
function ClientPage() {
  return (
    <>
      <Header heading="This is what you can do about your device !" />

      <div className=" flex justify-center  font-extrabold text-gray-900"></div>

      <CreateClient />
    </>
  );
}
export default sessionStorage.getItem("clientUID") ? ClientPage : LoginPage;
