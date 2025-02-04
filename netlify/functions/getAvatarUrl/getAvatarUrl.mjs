export const handler = async (event, context) => {
    const profileIdentifier = event.headers.profileidentifier;
    const apiKey = process.env.GRAVATAR_API_KEY;

    try {
        const response = await fetch(`https://api.gravatar.com/v3/profiles/${profileIdentifier}`, {
            method: 'GET',
            headers: {
                Authorization: apiKey,
            },
        });
        const data = await response.json();
        const avatar_url = `${data.avatar_url}?s=200`;
        return {
            statusCode: 200,
            body: JSON.stringify({ avatar_url }),
        };
    } catch (error) {
        return {
            statusCode: 500,
            body: JSON.stringify({ error: 'Failed to fetch avatar' }),
        };
    }
};
