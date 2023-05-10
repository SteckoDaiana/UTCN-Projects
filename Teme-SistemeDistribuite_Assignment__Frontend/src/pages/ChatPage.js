import ChatRoom from "../components/Chat/ChatRoom";
import LoginPage from "./Login";
function ChatPage() {
  return (
    <>
      <div className=" flex justify-center  font-extrabold text-gray-900">
        <h1>There is a place where you can talk: </h1>
      </div>

      <ChatRoom />
    </>
  );
}
export default sessionStorage.getItem("username") ? ChatPage : LoginPage;
