import Header from "../components/User/UserHeader";
import CreateUser from "../components/User/CreateUser";
import LoginPage from "./Login";
function CreateUserPage() {
  return (
    <>
      <Header heading="This is what you have to do to create an user !" />

      <div className=" flex justify-center  font-extrabold text-gray-900"></div>

      <CreateUser />
    </>
  );
}
export default sessionStorage.getItem("admUID") ? CreateUserPage : LoginPage;
