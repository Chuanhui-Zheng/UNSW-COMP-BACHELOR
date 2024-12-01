import request from 'sync-request';
import config from './config.json';

/* Original expression
let token1  = authRegisterV1( 'listalltest1@test.com', 'gamegamegame','blabla','blabla').token;
let token2  = authRegisterV1( 'listalltest2@test.com', 'spaspaspa', 'blabla', 'blabla').token;*/

const PASS = 200;
const FAIL = 400;
const Token_FAIL = 403;

const ERROR = {
    error: 'error',
};

describe('HTTP tests channelslistall', () => {
    //Create user
    const user1 = request(
        'POST',
        `${config.url}:${config.port}auth/register/v2`,
        {
            json: {
                "email" : 'listalltest1@test.com',
                "password" : 'gamegamegame',
                "nameFirst" : 'blabla',
                "nameLast" : 'blabla'
            }
        }
    );
    const myuser = JSON.parse(user1.getBody() as string);

    //Create channel1
    const channel1 = request(
        'POST',
        `${config.url}:${config.port}channels/create/v2`,
        {
            json: {
                "token" : myuser.token,
                "name" : 'channeltest1',
                "isPublic" : 1,
            }
        }
    );
    const mychannel1 = JSON.parse(channel1.getBody() as string);

    //Create channel2
    const channel2 = request(
        'POST',
        `${config.url}:${config.port}channels/create/v2`,
        {
            json: {
                "token" : myuser.token,
                "name" : 'channeltest2',
                "isPublic" : 1,
            }
        }
    );
    const mychannel2 = JSON.parse(channel2.getBody() as string);

    //User1 created channel1 & channel2

    test('Test type of array channels', () => {
        const channels_list = request(
            'GET',
            `${config.url}:${config.port}channels/listall/v2`,
            { 
                json: {
                    "token" : myuser.token,
                }
            }
        );
        const bodyObj = JSON.parse(channels_list.getBody() as string);
        expect(channels_list.statusCode).toBe(PASS);
        expect(bodyObj.channels).toStrictEqual(expect.any(Array));
    });

    test('Test invalid token', () => {
        const invalid_token = request(
            'GET',
            `${config.url}:${config.port}channels/listall/v2`,
            {
                json: {
                    token: asd,
                }
            }
        );
        const testtoken = JSON.parse(invalid_token.getBody() as string);
        expect(invalid_token.statusCode).toBe(Token_FAIL);
        expect(testtoken.authUserId).toStrictEqual(ERROR);
    });

    test('')
});

