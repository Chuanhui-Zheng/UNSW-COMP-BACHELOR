import {setData} from './dataStore.js'
function clearV1() {
  const obj = {
    user: [],
    channels: [],
    messages: [],
    globalFirst: true,
 };
  setData(obj);
  return {};
}

export { clearV1 };
