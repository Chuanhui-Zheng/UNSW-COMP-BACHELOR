import {channelsCreateV1} from './channels.js'
import {authRegisterV1, authLoginV1} from './auth.js'
import {channelMessagesV1} from './channel.js'
import {clearV1} from './other.js'

const users = [
    {email: 'haydens@gmail.com', password: 'helloworld', nameFirst: 'Hayden', nameLast: 'Smith',},
    {email: 'timmy@gmail.com', password: 'password', nameFirst: 'Timmy', nameLast: 'White',},
    {email: 'jsnow@gmail.com', password: 'winter"s coming', nameFirst: 'Jone', nameLast: 'Snow',},
];

const ERROR = {
    error: 'error',
};

// const mess_modules = [
//     'Hello World!',
//     'Let"s play Genshin Impact',
//     'Leave me alone, you yuanpy...',
//     'What party?',
//     'Winter"s Coming',
// ];

describe('BlackBox Testing: Pass cases (channelMessagesV1)', ()=>{
    let u_id, c_id;
    beforeEach(()=>{
        clearV1();
        u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
        expect(authLoginV1(users[0].email, users[0].password).authUserId).toBe(u_id);
        c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
    });

    test('Test: no messages', ()=>{
        expect(channelMessagesV1(u_id, c_id, 0)).toStrictEqual(
            expect.objectContaining({
                messages: [],
                start:  0,
                end:    -1,
            })
        );
    });

});

describe('BlackBox Testing: Fail cases (channelMessagesV1)', ()=>{
    let u_id, c_id;
    beforeEach(()=>{
        clearV1();
        u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
        expect(authLoginV1(users[0].email, users[0].password).authUserId).toBe(u_id);
        c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
    });

    test('Test: channel ID invalid', ()=>{
        expect(channelMessagesV1(u_id, c_id+1, 0)).toStrictEqual(ERROR);
        expect(channelMessagesV1(u_id, (c_id+2)*10, 0)).toStrictEqual(ERROR);
    });

    test('Test: negative cID input', ()=>{
        expect(channelMessagesV1(u_id, -(c_id+1), 0)).toStrictEqual(ERROR);
        expect(channelMessagesV1(u_id, (c_id+2)*-4, 0)).toStrictEqual(ERROR);
    });

    test('Test: user ID invalid', ()=>{
        expect(channelMessagesV1(u_id+1, c_id, 0)).toStrictEqual(ERROR);
        expect(channelMessagesV1((c_id+2)*10, c_id, 0)).toStrictEqual(ERROR);
    });

    test('Test: negative uID input', ()=>{
        expect(channelMessagesV1(-(u_id+1), c_id, 0)).toStrictEqual(ERROR);
        expect(channelMessagesV1((u_id+2)*-4, c_id, 0)).toStrictEqual(ERROR);
    });
    
    test('Test: start exceeds maximum amount of messages', ()=>{
        expect(channelMessagesV1(u_id, c_id, 1)).toStrictEqual(ERROR);
        expect(channelMessagesV1(u_id, c_id, 20)).toStrictEqual(ERROR);
    });

    test('Test: negative start input', ()=>{
        expect(channelMessagesV1(u_id, -c_id, -1)).toStrictEqual(ERROR);
        expect(channelMessagesV1(u_id, c_id, -10)).toStrictEqual(ERROR);
    });

    test('Test: user is not a member of channel', ()=>{
        let u_id_1 = authRegisterV1(users[1].email, users[1].password, users[1].nameFirst, users[1].nameLast).authUserId;
        expect(channelMessagesV1(u_id_1, c_id, 0)).toStrictEqual(ERROR);
        
        let u_id_2 = authRegisterV1(users[2].email, users[2].password, users[2].nameFirst, users[2].nameLast).authUserId;
        expect(channelMessagesV1(u_id_2, c_id, 0)).toStrictEqual(ERROR);
    });

});
    // test('Test: only 1 message', ()=>{
    //     u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
    //     c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
    //     fill(c_id, u_id, mess_modules, 1);
    //     expect(channelMessagesV1(u_id, c_id, 0)).toStrictEqual(
    //         expect.objectContaining({
    //             messages:   expect.any(Array),
    //             start:      0,
    //             end:        -1,
    //         })
    //     );
    // });

    // test('Test: less than 50 messages', ()=>{
    //     u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
    //     c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
    //     fill(c_id, u_id, mess_modules, 49);
    //     expect(channelMessagesV1(u_id, c_id, 0)).toStrictEqual(
    //         expect.objectContaining({
    //             messages:   expect.any(Array),
    //             start:      0,
    //             end:        -1,
    //         })
    //     );
    // });

    // test('Test: 50 messages', ()=>{
    //     u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
    //     c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
    //     fill(c_id, u_id, mess_modules, 50);
    //     expect(channelMessagesV1(u_id, c_id, 0)).toStrictEqual(
    //         expect.objectContaining({
    //             messages:   expect.any(Array),
    //             start:      0,
    //             end:        -1,
    //         })
    //     );
    // });

    // test('Test: over 50 messages', ()=>{
    //     u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
    //     c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
    //     fill(c_id, u_id, mess_modules, 51);
    //     expect(channelMessagesV1(u_id, c_id, 0)).toStrictEqual(
    //         expect.objectContaining({
    //             messages:   expect.any(Array),
    //             start:      0,
    //             end:        50,
    //         })
    //     );
    // });


// describe('WhiteBox Testing (channelMessagesV1)', ()=>{
//     let u_id;
//     let c_id;
//     beforeEach(()=>{
//         clearV1();
//     })

//     test('Test: channel ID invalid', ()=>{
//         u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
//         c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
//         fill(c_id, u_id, mess_modules, 1);
//         expect(channelMessagesV1(u_id, c_id+1, 0)).toStrictEqual(ERROR);
//     });
    
//     test('Test: start exceeds maximum amount of messages', ()=>{
//         u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
//         c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
//         fill(c_id, u_id, mess_modules, 1);
//         expect(channelMessagesV1(u_id, c_id, 1)).toStrictEqual(ERROR);
//         expect(channelMessagesV1(u_id, c_id, 20)).toStrictEqual(ERROR);
//     });

//     test('Test: user is not a member of channel', ()=>{
//         u_id = authRegisterV1(users[0].email, users[0].password, users[0].nameFirst, users[0].nameLast).authUserId;
//         let u_id_1 = authRegisterV1(users[1].email, users[1].password, users[1].nameFirst, users[1].nameLast).authUserId;
//         c_id = channelsCreateV1(u_id, 'New Channel', true).channelId;
//         fill(c_id, u_id, mess_modules, 1);
//         expect(channelMessagesV1(u_id_1, c_id, 1)).toStrictEqual(ERROR);
//     });

// });


// function fill(channelId, uId, module, times) {
//     for (let i = 0; i < times; i++) {
//         sendMessages(channelId, uId, module[i % 5]);
//     }
// }

// function sendMessages(channelId, uId, mess) {
//     let data = getData();
//     let messages = data.messages;
    
//     messages.unshift({
//         messId: messages.length,
//         uId:  uId,
//         message:  mess,
//         timeSent: channelId+uId,
//     });
    
//     data.channels[channelId].messages.unshift(messages.length-1);
//     setData(data);
// }
