function channelDetailsV1(authUserId, channelId) {
  return {
    name: 'Hayden',
    ownerMembers: [
      {
        uId: 1,
        email: 'example@gmail.com',
        nameFirst: 'Hayden',
        nameLast: 'Jacobs',
        handleStr: 'haydenjacobs',
      }
    ],
    allMembers: [
      {
        uId: 1,
        email: 'example@gmail.com',
        nameFirst: 'Hayden',
        nameLast: 'Jacobs',
        handleStr: 'haydenjacobs',
      }
    ],
  }
}
  
function channelJoinV1(authUserId, channelId) {
  return {}
}

function channelInviteV1(authUserId, channelId, uId) {
  return {}
}
  
function channelMessagesV1 (authUserId, channelId, start) {
  if (!checkUserValid(authUserId) || !checkChannelValid(channelId) || !checkMembership(authUserId, channelId)) return {error: 'error'};
  let data = getData().channels[channelId].messages;
  if (start > data.length || start < 0) return {error: 'error'};

  let messages = getData().messages;
  let end = (data.length > 50) ? (start + 50) : -1;
  let mess = [];
  for (let i of data) {
          mess.push(messages[messages.length - (i + 1)])
  }

  return {
          messages:  mess,
          start:  start,
          end:    end,
  };
}

//=== channelMessagesV1 Helpers ===:

function checkUserValid(uId) {
  if (typeof uId != 'number' || uId < 0) return false;
  let data = getData().user;
  for (let u of data) {
    if (u.uId == uId) return true;
  }
  return false;
}

function checkChannelValid(channelId) {
  if (typeof channelId != 'number' || channelId < 0) return false;
  let data = getData().channels;
  return (data.findIndex(i => i.channelId == channelId) !== -1);
}

function checkMembership(authUserId, channelId) {
  let data = getData().channels;
  let cId = data.findIndex(i => i.channelId === channelId);
  return (data[cId].allMembers.findIndex(i => i.uId === authUserId) !== -1);
}